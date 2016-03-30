/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Jason Booth
Copyright (c) 2009      Robert J Payne
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __SPRITE_CCSPRITE_FRAME_CACHE_H__
#define __SPRITE_CCSPRITE_FRAME_CACHE_H__

/*
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */
#include <set>
#include <string>
#include "2d/CCSpriteFrame.h"
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "base/CCMap.h"

NS_CC_BEGIN

class Sprite;
class Texture2D;

/**
 * @addtogroup _2d
 * @{
 */

/** @class SpriteFrameCache
 * @brief Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
 @since v0.9
 @js cc.spriteFrameCache
 */
class CC_DLL SpriteFrameCache : public Ref
{
public:
    /** Returns the shared instance of the Sprite Frame cache.
     *
     * @return The instance of the Sprite Frame Cache.
     * @js NA
     */
    static SpriteFrameCache* getInstance();

    /** Destroys the cache. It releases all the Sprite Frames and the retained instance.
     * @js NA
     */
    static void destroyInstance();

    /** Destructor.
     * @js NA
     * @lua NA
     */
    virtual ~SpriteFrameCache();
    
    /** Initialize method.
     *
     * @return if success return true.
     */
    bool init();

    /** Adds multiple Sprite Frames from a plist file.
     * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png.
     * If you want to use another texture, you should use the addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName) method.
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     */
    void addSpriteFramesWithFile(const std::string& plist);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
     @since v0.99.5
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     * @param textureFileName Texture file name.
     */
    void addSpriteFramesWithFile(const std::string& plist, const std::string& textureFileName);

    /** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames. 
     * @js addSpriteFrames
     * @lua addSpriteFrames
     *
     * @param plist Plist file name.
     * @param texture Texture pointer.
     */
    void addSpriteFramesWithFile(const std::string&plist, Texture2D *texture);

    /** Adds multiple Sprite Frames from a plist file content. The texture will be associated with the created sprite frames. 
     * @js NA
     * @lua addSpriteFrames
     *
     * @param plist_content Plist file content string.
     * @param texture Texture pointer.
     */
    void addSpriteFramesWithFileContent(const std::string& plist_content, Texture2D *texture);

    /** Adds an sprite frame with a given name.
     If the name already exists, then the contents of the old name will be replaced with the new one.
     *
     * @param frame A certain sprite frame.
     * @param frameName The name of the sprite frame.
     */
    void addSpriteFrame(SpriteFrame *frame, const std::string& frameName);

    /** Check if multiple Sprite Frames from a plist file have been loaded.
    * @js NA
    * @lua NA
    *
    * @param plist Plist file name.
    * @return True if the file is loaded.
    */
    bool isSpriteFramesWithFileLoaded(const std::string& plist) const;

    /** Purges the dictionary of loaded sprite frames.
     * Call this method if you receive the "Memory Warning".
     * In the short term: it will free some resources preventing your app from being killed.
     * In the medium term: it will allocate more resources.
     * In the long term: it will be the same.
     */
    void removeSpriteFrames();

    /** Removes unused sprite frames.
     * Sprite Frames that have a retain count of 1 will be deleted.
     * It is convenient to call this method after when starting a new Scene.
     * @js NA
     */
    void removeUnusedSpriteFrames();

    /** Deletes an sprite frame from the sprite frame cache. 
     *
     * @param name The name of the sprite frame that needs to removed.
     */
    void removeSpriteFrameByName(const std::string& name);

    /** Removes multiple Sprite Frames from a plist file.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    * @since v0.99.5
    *
    * @param plist The name of the plist that needs to removed.
    */
    void removeSpriteFramesFromFile(const std::string& plist);

    /** Removes multiple Sprite Frames from a plist file content.
    * Sprite Frames stored in this file will be removed.
    * It is convenient to call this method when a specific texture needs to be removed.
    *
    * @param plist_content The string of the plist content that needs to removed.
    * @js NA
    */
    void removeSpriteFramesFromFileContent(const std::string& plist_content);

    /** Removes all Sprite Frames associated with the specified textures.
     * It is convenient to call this method when a specific texture needs to be removed.
     * @since v0.995.
     *
     * @param texture The texture that needs to removed.
     */
    void removeSpriteFramesFromTexture(Texture2D* texture);

    /** Returns an Sprite Frame that was previously added.
     If the name is not found it will return nil.
     You should retain the returned copy if you are going to use it.
     * @js getSpriteFrame
     * @lua getSpriteFrame
     *
     * @param name A certain sprite frame name.
     * @return The sprite frame.
     */
    SpriteFrame* getSpriteFrameByName(const std::string& name);

protected:
    // MARMALADE: Made this protected not private, as deriving from this class is pretty useful
    SpriteFrameCache(){}

    /*Adds multiple Sprite Frames with a dictionary. The texture will be associated with the created sprite frames.
     */
    void addSpriteFramesWithDictionary(ValueMap& dictionary, Texture2D *texture);

    /** Removes multiple Sprite Frames from Dictionary.
    * @since v0.99.5
    */
    void removeSpriteFramesFromDictionary(ValueMap& dictionary);


    Map<std::string, SpriteFrame*> _spriteFrames;
    ValueMap _spriteFramesAliases;
    std::set<std::string>*  _loadedFileNames;
};

// end of _2d group
/// @}

NS_CC_END

#endif // __SPRITE_CCSPRITE_FRAME_CACHE_H__
