#pragma once

#if _DEBUG && false ///< Set true for leak detection with file names and line numbers
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new     DBG_NEW

#endif

#include "Debug.hpp"
#include "targetver.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <algorithm>
#include <box2d/box2d.h>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
