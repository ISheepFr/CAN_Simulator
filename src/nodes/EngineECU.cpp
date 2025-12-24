#include "EngineECU.h"
#include "../can/CANBus.h"


#include <QRandomGenerator>

EngineECU::EngineECU(CANBus* bus, int periodMS,int simulationPeriodMS)
    : CANNode{"EngineECU", bus},
    d_rpm{800},
    d_temp{75},
    d_load{0},
    lastTime{QDateTime::currentMSecsSinceEpoch()}
{
    QObject::connect(&d_timer, &QTimer::timeout,this, &EngineECU::onTimeout);
    d_timer.start(periodMS);

    QObject::connect(&d_simTimer, &QTimer::timeout,this, &EngineECU::onSimTimeout);
    d_simTimer.start(simulationPeriodMS);
}

void EngineECU::onTimeout()
{
    //updateEngineState();
    sendEngineFrame();
}

void EngineECU::onSimTimeout()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    d_deltaTime = (currentTime - lastTime) / 1000.0;  // Convertir en secondes
    lastTime = currentTime;
    qDebug() << "deltatime = " << d_deltaTime;
    updateEngineState();  // Mettre à jour l'état du moteur
}

void EngineECU::updateEngineState()
{
    /*if(d_pedal_valid)
    {
        d_rpm_target = 800 + d_pedal * (6000 - 800) / 100;
        d_rpm += (d_rpm_target - d_rpm) * 0.1 * d_deltaTime;
    }
    else
    {
        d_rpm -= 50 * d_deltaTime;
        if(d_rpm < 800)
        {
            d_rpm = 800;
        }
    }

    d_speed_target = static_cast<uint16_t>(d_rpm * 0.02f);
    d_speed += static_cast<uint16_t>((d_speed_target - d_speed) * 0.1f * d_deltaTime);
*/
    // Constantes moteur / sportive
    constexpr float idleRpm   = 800.0f;
    constexpr float maxRpm    = 6000.0f;
    constexpr float tauRpm    = 0.2f;       // moteur réactif
    constexpr float maxAccel  = 8.0f;       // m/s² pédale max
    constexpr float airResist = 0.015f;     // résistance à l'air
    constexpr float gearRatios[5] = {140.0f, 100.0f, 70.0f, 50.0f, 25.0f}; // RPM/km/h

    static float speedF = 0.0f;  // km/h float interne
    static float rpmF   = 800.0f;
    static int currentGear = 0;

    // Facteur pédale
    float pedalFactor = d_pedal_valid ? d_pedal / 100.0f : 0.0f;

    // Accélération moteur
    float accel = pedalFactor * maxAccel;

    // Conversion km/h → m/s pour calcul physique
    float speedMps = speedF / 3.6f;

    // Décélération due à air/frottements
    float decelAir = airResist * speedMps * speedMps;

    // Accélération nette
    float accelNet = pedalFactor > 0.0f ? accel - decelAir : -decelAir;

    // Mise à jour vitesse
    speedMps += accelNet * d_deltaTime;
    if (speedMps < 0.0f) speedMps = 0.0f;
    speedF = speedMps * 3.6f; // km/h

    // Sélection du meilleur rapport (le plus haut possible sans dépasser maxRpm)
    int bestGear = 0;
    float rpmTarget = maxRpm;

    for (int gear = 0; gear < 5; ++gear) {
        float projectedRPM = speedF * gearRatios[gear];
        if (projectedRPM <= maxRpm) {
            bestGear = gear;       // garder le rapport le plus haut possible
            rpmTarget = projectedRPM;
        }
    }

    currentGear = bestGear;

    // Clamp RPM pour sécurité
    rpmTarget = std::clamp(rpmTarget, idleRpm, maxRpm);

    // Mise à jour RPM dynamique
    rpmF += (rpmTarget - rpmF) * (d_deltaTime / tauRpm);

    // Stockage pour CAN
    d_speed = static_cast<uint16_t>(speedF);
    d_rpm   = static_cast<uint16_t>(rpmF);

}

void EngineECU::sendEngineFrame()
{
    /*d_rpm = QRandomGenerator::global()->bounded(0,9000);
    d_temp = QRandomGenerator::global()->bounded(0,200);
    d_load = QRandomGenerator::global()->bounded(0,100);*/

    QByteArray data(8,0);
    data[0] = static_cast<char>((d_rpm >> 8) & 0xFF);
    data[1] = static_cast<char>(d_rpm & 0xFF);
    data[2] = static_cast<char>(d_pedal);
    data[3] = static_cast<char>(75);
    data[4] = static_cast<char>((d_speed >> 8) & 0xFF);
    data[5] = static_cast<char>(d_speed & 0xFF);

    CANFrame frame(0x100,data);
    this->sendFrame(frame);
}

void EngineECU::receiveFrame(const CANFrame& frame)
{
    if(frame.getD_id() == 0x090 && frame.getD_dlc() == 8)
    {
        d_pedal = static_cast<uint8_t>(frame.getD_data()[0]);
        d_pedal_valid = frame.getD_data()[1];
    }
}


