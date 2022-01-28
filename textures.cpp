#include <iostream>
#include <GL/gl.h>

#include "textures.h"
#include "pngutil.h"

Texture::Texture(const char *filename) :
texture_(0) {
    loadFromFile(filename);
}

Texture::~Texture() {
    if (texture_) {
        glDeleteTextures(1, &texture_);
    }
}

void Texture::loadFromFile(const char * filename) {
    FILE *file = fopen(filename, "rb");

    if (!file) {
        std::cerr << filename << " can\'t open" << std::endl;
    }

    if (pnguIsPng(file) == 0) {
        std::cerr << filename << " is not PNG" << std::endl;
        fclose(file);
        return;
    }

    int bytesPerPixel = 0;
    pnguReadHeader(file, &width_, &height_, &bytesPerPixel);

    if (bytesPerPixel != 4) {
        std::cerr << filename << " is not RGBA_8888" << std::endl;
        fclose(file);
    }

    const auto pixels = readPixels(file);

    fclose(file);

    createOpenglTexture(pixels.data());
}

std::vector< unsigned char > Texture::readPixels(FILE *file) const {
    constexpr int bytesPerPixel = 4;
    std::vector<unsigned char> pixels(width_ * height_ * bytesPerPixel);
    pnguReadData(file, pixels.data());
    return pixels;
}

void Texture::createOpenglTexture(const unsigned char *bytes) {
    glGenTextures(1, &texture_);

    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, texture_);
}

int Texture::width() const {
    return width_;
}

int Texture::height() const {
    return height_;
}
