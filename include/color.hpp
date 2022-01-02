
class Color{

    public:
    float red;
    float green;
    float blue;

    Color();
    Color(float r, float g, float b);

    Color operator + (float scalar);
    Color operator - (float scalar);
    Color operator * (float scalar);
    //blend colors using Haramard product
    Color operator * (Color& inColor);
    void operator = (Color& inColor);
    ~Color();
};