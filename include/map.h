#ifndef MAP_H
#define MAP_H
#include "raytmx.h"
#include <vector>
#include "torch.h"

class Map
{
private:
    TmxMap *map;
    Vector2 spawnPos;
   // int groundLayerIndex;
    int objectLayerIndex;

    std::vector<Rectangle> collisionBoxes;
    std::vector<Vector2> torchPositions;


public:
    Map();
    ~Map();
    bool Load(const char *filepath);
    void Draw(int posX, int posY, Color tint);
    Vector2 GetSpawnPosition();
    void Unload();
    const TmxLayer* GetLayer(int index) const;
    const std::vector<Rectangle>& GetCollisionBoxes() const;
    const std::vector<Vector2>& GetTorchPositions() const;
    
   

};

#endif