#include "LasReader.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

using namespace std;

int main(int argc, char *argv[])
{
    LASReader vReader("./LidarData/htp.las");

    vector<float3> vPoints = vReader.getLidarPoints();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LiDARMesh", "Main");

    return QGuiApplication::exec();
}
