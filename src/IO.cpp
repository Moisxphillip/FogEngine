#include "../lib/IncludeAll.hpp"

bool IO::ReadToBuffer(std::string Path, std::vector<unsigned char>& Buffer)
{
    std::ifstream File(Path, std::ios::binary);
    if(File.fail())
    {
        Error("IO::ReadToBuffer: Failed to read file");
        return false;
    }

    //Go to the end, take size and go back to the beginning of a file
    File.seekg(0, std::ios::end);
    std::cout << File.tellg();
    int Size = File.tellg();
    File.seekg(0, std::ios::beg);
    Size-= File.tellg(); //Remove file header size
    
    Buffer.resize(Size);
    File.read((char*)&Buffer[0],Size);
    File.close();
    
    return true;
}

GLTexture IO::LoadPNG(std::string Path)
{
    GLTexture Texture{0,0,0};
    std::vector<unsigned char> Input, Output;
    unsigned long w, h;
    if(!ReadToBuffer(Path, Input))
    {
        Error("IO::LoadPNG: Failed on copying "+ Path + " to buffer");
    }

    if(decodePNG(Output, w, h, &Input[0], Input.size()) != 0)
    {
        Error("IO::LoadPNG: Failed decoding "+ Path);
    }

    glGenTextures(1, &Texture.ID);
    glBindTexture(GL_TEXTURE_2D, Texture.ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &Output[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    Texture.W = w;
    Texture.H = h;
    return Texture;
}