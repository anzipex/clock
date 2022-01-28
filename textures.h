#pragma once

#include <vector>

/**
 * @brief Texture class. Works with textures
 */
class Texture {
public:
    explicit Texture(const char *filename);
    ~Texture();

    /**
     * @brief Bind texture
     */
    void bind() const;

    /**
     * @brief Texture width
     * @return width value
     */
    int width() const;

    /**
     * @brief Texture height
     * @return height
     */
    int height() const;

private:
    int width_;
    int height_;
    unsigned int texture_;

    void createOpenglTexture(const unsigned char *pixels); //!< texture creation
    void loadFromFile(const char *filename); //!< load texture from file
    std::vector<unsigned char> readPixels(FILE *file) const; //!< vector of pixels
};
