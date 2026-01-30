#ifndef MAP_H
#define MAP_H
#include "raytmx.h"
#include <vector>

class Map
{
private:
    TmxMap *map;
    Vector2 spawnPos;
   // int groundLayerIndex;
    int objectLayerIndex;

    std::vector<Rectangle> collisionBoxes;

public:
    Map();
    ~Map();
    bool Load(const char *filepath);
    void Draw(int posX, int posY, Color tint);
    Vector2 GetSpawnPosition();
    void Unload();
    const TmxLayer* GetLayer(int index) const;
    const std::vector<Rectangle>& GetCollisionBoxes() const;

};

#endif