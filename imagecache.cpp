#include "imagecache.h"
#include "settingsmanager.h"

#include <QDirIterator>
#include <QDebug>
#include <stdexcept>

ImageCache* ImageCache::instance = NULL;

ImageCache* ImageCache::init()
{
    if (instance != NULL)
        throw new std::runtime_error("ImageCache is already inited.");

    instance = new ImageCache();
    return instance;
}

ImageCache* ImageCache::getInstance()
{
    if (instance == NULL)
        throw new std::runtime_error("ImageCache is not inited.");

    return instance;
}

ImageCache::ImageCache()
{
    loadTypeFromFolder(SpriteImg, "sprites");
    loadTypeFromFolder(TileOverlay, "tileoverlays");
    loadTypeFromFolder(TileOverride, "tileoverrides");
    loadTypeFromFolder(EntranceImg, "entrances");
    loadTypeFromFolder(TileCollision, "tilecollisions");

}

ImageCache::~ImageCache()
{
    for (int i = cache.size() - 1; i >= 0; i--)
        delete cache.values().at(i);
}


QPixmap ImageCache::get(CacheImgType type, QString name)
{
    return cache.value(type)->value(name);
}

void ImageCache::loadTypeFromFolder(CacheImgType type, QString folder)
{
    QHash<QString, QPixmap>* imgCache = new QHash<QString, QPixmap>();

    QDirIterator imgIterator(SettingsManager::getInstance()->dataPath(folder + "/"), QStringList() << "*.png", QDir::Files, QDirIterator::Subdirectories);
    quint32 folderLength = imgIterator.path().length();

    while (imgIterator.hasNext())
    {
        QString path = imgIterator.next();
        imgCache->insert(path.mid(folderLength), QPixmap(path));
    }

    cache.insert(type, imgCache);
}
