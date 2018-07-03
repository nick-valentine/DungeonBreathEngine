#ifndef MACROS_H
#define MACROS_H

#define DEBUG 0
#define DATADIR "./GameData/"
#define IMGDIR DATADIR "img/"
#define LANGDIR DATADIR "lang/"
#define LEVELDIR DATADIR "levels/"
#define TILESETDIR DATADIR "tilesets/"
#define SCRIPTDIR DATADIR "scripts/"
#define AUDIODIR DATADIR "sound/"

// actordir is not a full path as Script.h automatically prepends SCRIPTDIR
#define ACTORDIR "actors/"
#define WORLDSCRIPTDIR "levels/"
#define SCENEDIR "scenes/"

#define WINDOWS 1
#define LINUX 0

#endif //MACROS_H
