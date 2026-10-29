#include "LASReader.h"

#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

LASReader::LASReader(QObject *parent)
    : QObject{parent}
{

}

LASReader::LASReader(const std::string &lasFilePath)
{
    ReadLasFile(lasFilePath);
}

void LASReader::ReadLasFile(const std::string &lasFilePath)
{
    ifstream inf(lasFilePath, ios::binary);

    if (!inf.is_open())
    {
        throw runtime_error("LAS read error");
    }

    LASHeader vHeader;

    inf.read(reinterpret_cast<char*>(&vHeader), sizeof(LASHeader));

    assert(vHeader.versionMajor == 1 && vHeader.versionMinor == 4);
    assert(vHeader.headerSize == sizeof(LASHeader));
    assert(vHeader.pointDataRecordFormat == 6);

    inf.seekg(vHeader.offsetToPointData);
    for (uint32_t i = 0; i < vHeader.numberOfPointRecords; i++)
    {
        if (!inf.good())
        {
            cout << i << '\n';
            throw runtime_error("Error reading file");
        }

        LASPointFormat6 vPoint;

        inf.read(reinterpret_cast<char*>(&vPoint), sizeof(LASPointFormat6));
        m_lidarPoints.emplace_back(vPoint.x * vHeader.xScale + vHeader.xOffset,
                                   vPoint.y * vHeader.yScale + vHeader.yOffset,
                                   vPoint.z * vHeader.zScale + vHeader.zOffset);
    }
}

bool float3::operator==(float3 &Other)
{
    return (X == Other.X && Y == Other.Y && Z == Other.Z);
}

std::vector<float3> LASReader::getLidarPoints() const
{
    return m_lidarPoints;
}

float LASReader::getX() const
{
    return m_lidarPoints[0].X;
}


std::string LASReader::getXStr() const
{
    return to_string(m_X);
}

QString LASReader::getXQStr() const
{
    return "123456";
}
