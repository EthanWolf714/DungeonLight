#include "map.h"
#include "raytmx.h"
Map::Map()
{
    // init map as null so map!= null check doesn't pass
    map = NULL;
    objectLayerIndex = -1;
    spawnPos = {40.0f, 40.0f};
}

Map::~Map()
{
    Unload();
}

void Map::Unload()
{
    //TraceLog(LOG_INFO, "=== Unload() START ===");
    if (map != NULL)
    {
         TraceLog(LOG_INFO, "Unloading TMX...");
        UnloadTMX(map);
        map = NULL;
        TraceLog(LOG_INFO, "TMX unloaded");
    }
    objectLayerIndex = -1;

   // collisionBoxes.clear();
    spawnPos = {40.0f, 40.0f};
}

bool Map::Load(const char *filepath)
{
    
    Unload();

    // initialize tile map
    map = LoadTMX(filepath);

    if (map == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to load TMX map");
        return false;
    }
    TraceLog(LOG_INFO, "Map Loaded Successfully!");

    // loop through tilemap layers
    for (unsigned int i = 0; i < map->layersLength; i++)
    {
        const TmxLayer layer = map->layers[i];

        if (layer.name != NULL)
        {
            //find layers
            if (strcmp(layer.name, "Objects") == 0)
            {
                objectLayerIndex = i;
            }
        }
        // loop through objects group
        if (layer.type == LAYER_TYPE_OBJECT_GROUP)
        {
            TmxObjectGroup objGroup = layer.exact.objectGroup;


            //check if layer is the Walls layer
            bool isWallsLayer =  (layer.name != NULL && strcmp(layer.name, "Walls") == 0);

            // loop through object layer
            for (unsigned int j = 0; j < objGroup.objectsLength; j++)
            {
                const TmxObject object = objGroup.objects[j];
                // location spawn point object

                if (object.name != NULL)
                {
                    if (strcmp(object.name, "spawn") == 0)
                    {
                        // offset spawn positition for player sprite
                        spawnPos.x = object.x - 8;
                        spawnPos.y = object.y - 8;
                        TraceLog(LOG_INFO, "Spawn object position: x=%.2f, y=%.2f", object.x, object.y);
                        // TraceLog(LOG_INFO, "Spawn object size: w=%.2f, h=%.2f", object.width, object.height);
                    }else if(strcmp(object.name, "torch") == 0){
                        torchPositions.push_back({(float)object.x, (float)object.y});
                        TraceLog(LOG_INFO, "Loaded %d torches", torchPositions.size());
                    }
                    else if (isWallsLayer)
                    {
                        collisionBoxes.push_back(Rectangle{
                            (float)object.x,
                            (float)object.y,
                            (float)object.width,
                            (float)object.height});
                    }
                }
            }
        }
    }

    return true;
}

void Map::Draw(int posX, int posY, Color tint)
{
    if (map != NULL)
    {
        DrawTMX(map, NULL, NULL, posX, posY, tint);
    }
}

Vector2 Map::GetSpawnPosition(){
    return spawnPos;
}

const TmxLayer *Map::GetLayer(int index) const
{
    if (map != NULL && index >= 0 && index < (int)map->layersLength)
    {
        return &map->layers[index];
    }
    return nullptr;
}

const std::vector<Rectangle> &Map::GetCollisionBoxes() const
{
    return collisionBoxes;
}

const std::vector<Vector2>& Map::GetTorchPositions() const
{
    return torchPositions;
}