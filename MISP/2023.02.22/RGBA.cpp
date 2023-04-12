export module RGBA;

import <iostream>;
import <iomanip>;
import <bitset>;

export enum PrintType
{
    E_RGBA,
    E_HEX,
    E_INT
};

export class RGBA
{
    private:
        int red, green, blue, alpha;

    public:
        RGBA()
        {
            red = 0;
            green = 0;
            blue = 0;
            alpha = 255;
        }

        RGBA(int red, int green, int blue, int alpha = 255)
        {
            this->red = red > 255 ? 255 : red;
            this->green = green > 255 ? 255 : green;
            this->blue = blue > 255 ? 255 : blue;
            this->alpha = alpha > 255 ? 255 : alpha;
        }

        RGBA(const RGBA& rgba)
        {
            this->red = rgba.getRed();
            this->green = rgba.getGreen();
            this->blue = rgba.getBlue();
            this->alpha = rgba.getAlpha();
        }

        int getRed() const
        {
            return red;
        }

        int getGreen() const
        {
            return green;
        }

        int getBlue() const
        {
            return blue;
        }

        int getAlpha() const
        {
            return alpha;
        }

        void setColor()
        {
            red = 0;
            green = 0;
            blue = 0;
            alpha = 255;
        }

        void setColor(int red, int green, int blue, int alpha = 255)
        {
            this->red = red > 255 ? 255 : red;
            this->green = green > 255 ? 255 : green;
            this->blue = blue > 255 ? 255 : blue;
            this->alpha = alpha > 255 ? 255 : alpha;
        }

        void print(const PrintType& type = E_RGBA) const
        {
            switch(type)
            {
                case E_RGBA:
                    {
                        std::cout << red << " ";
                        std::cout << green << " ";
                        std::cout << blue << " ";
                        std::cout << alpha << std::endl;
                        break;
                    }

                case E_HEX:
                    {
                        std::cout << "#";
                        std::cout << std::hex << red;
                        std::cout << std::hex << green;
                        std::cout << std::hex << blue;
                        std::cout << std::hex << alpha;
                        std::cout << std::endl;
                        break;
                    }

                case E_INT:
                    {
                        auto result = std::bitset<32>((unsigned int) ((red << 24) | (green << 16) | (blue << 8) | alpha)).to_string();
                        std::cout << result << std::endl;
                        break;
                    }
            }
        }

        RGBA sum(const RGBA& rgba) const
        {
            int r = this->red + rgba.getRed() > 255 ? 255 : this->red + rgba.getRed();
            int g = this->green + rgba.getGreen() > 255 ? 255 : this->green + rgba.getGreen();
            int b = this->blue + rgba.getBlue() > 255 ? 255 : this->blue + rgba.getBlue();
            int a = this->alpha + rgba.getAlpha() > 255 ? 255 : this->alpha + rgba.getAlpha();
            return RGBA(r, g, b, a);
        }
};






