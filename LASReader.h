#ifndef LASREADER_H
#define LASREADER_H

#include <QObject>
#include <qqml.h>

#include <cstdint>
#include <string>
#include <vector>

struct float3 {
    float X, Y, Z;
public:
    float3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    bool operator==(float3 &Other);
};

class LASReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(std::vector<float3> lidarPoints READ getLidarPoints)
    Q_PROPERTY(float X READ getX)
    Q_PROPERTY(std::string XStr READ getXStr)
    Q_PROPERTY(QString XQStr READ getXQStr)
    QML_ELEMENT
private:

#pragma pack(push, 1)
    struct LASHeader
    {
        char signature[4];
        uint16_t fileSourceID;
        uint16_t globalEncoding;
        uint32_t guidData1;
        uint16_t guidData2;
        uint16_t guidData3;
        uint8_t guidData4[8];
        uint8_t versionMajor;
        uint8_t versionMinor;
        char systemIdentifier[32];
        char generatingSoftware[32];
        uint16_t creationDay;
        uint16_t creationYear;
        uint16_t headerSize;
        uint32_t offsetToPointData;
        uint32_t numVLR;
        uint8_t pointDataRecordFormat;
        uint16_t pointDataRecordLength;
        uint32_t legacyNumberOfPointRecords;
        uint32_t legacyNumberOfPointByReturn[5];
        double xScale, yScale, zScale;
        double xOffset, yOffset, zOffset;
        double xMax, xMin, yMax, yMin, zMax, zMin;
        uint64_t startOfWaveformDataPacketRecord;
        uint64_t startOfFirstExtendedVLR;
        uint32_t numberOfExtendedVLR;
        uint64_t numberOfPointRecords;
        uint64_t numberOfPointsByReturn[15];
    };
#pragma pack(pop)

#pragma pack(push, 1)
    struct LASPointFormat6
    {
        long x, y, z;
        uint16_t intensity;
        uint16_t flags;
        uint8_t classification;
        uint8_t userData;
        int16_t scanAngle;
        uint16_t pointSourceID;
        int64_t gpsTime;
    };
#pragma pack(pop)


    std::vector<float3> m_lidarPoints;

    void ReadLasFile(const std::string &lasFilePath);

    float m_X;

    std::string m_XStr;

    QString m_XQStr;

public:
    explicit LASReader(QObject* parent = nullptr);
    LASReader(const std::string &lasFilePath);
    ~LASReader() = default;

    std::vector<float3> getLidarPoints() const;
    float getX() const;
    std::string getXStr() const;
    QString getXQStr() const;
};

#endif // LASREADER_H
