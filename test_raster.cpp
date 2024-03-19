// (c) www.scratchapixel.com

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cstdint>

typedef float Vec2[2];
typedef float Vec3[3];
typedef unsigned char Rgb[3];

inline
float edgeFunction(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
    return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
}

int main(int argc, char **argv) {
    Vec3 v2 = {-48, -10, 82};
    Vec3 v1 = {29, -15, 44};
    Vec3 v0 = {13, 34, 114};
    Vec3 c2 = {1, 0, 0};
    Vec3 c1 = {0, 1, 0};
    Vec3 c0 = {0, 0, 1};
    
    const uint32_t w = 512;
    const uint32_t h = 512;
    
    // Project triangle onto the screen
    v0[0] /= v0[2], v0[1] /= v0[2];
    v1[0] /= v1[2], v1[1] /= v1[2];
    v2[0] /= v2[2], v2[1] /= v2[2];
    // Convert from screen space to NDC then raster (in one go)
    v0[0] = (1 + v0[0]) * 0.5 * w, v0[1] = (1 + v0[1]) * 0.5 * h;
    v1[0] = (1 + v1[0]) * 0.5 * w, v1[1] = (1 + v1[1]) * 0.5 * h;
    v2[0] = (1 + v2[0]) * 0.5 * w, v2[1] = (1 + v2[1]) * 0.5 * h;

#ifdef PERSP_CORRECT
    // Divide vertex-attribute by the vertex z-coordinate
    c0[0] /= v0[2], c0[1] /= v0[2], c0[2] /= v0[2];
    c1[0] /= v1[2], c1[1] /= v1[2], c1[2] /= v1[2];
    c2[0] /= v2[2], c2[1] /= v2[2], c2[2] /= v2[2];
    // Pre-compute 1 over z
    v0[2] = 1 / v0[2], v1[2] = 1 / v1[2], v2[2] = 1 / v2[2];
#endif
    
    Rgb *framebuffer = new Rgb[w * h];
    memset(framebuffer, 0, w * h * 3);
    
    float area = edgeFunction(v0, v1, v2);
    
	printf("%f %f %f | %f\n", v0[2], v1[2], v2[2], area);

    for (uint32_t j = 0; j < h; ++j) {
        for (uint32_t i = 0; i < w; ++i) {
            Vec3 p = {i + 0.5f, h - j + 0.5f, 0.0};
            float w0 = edgeFunction(v1, v2, p);
            float w1 = edgeFunction(v2, v0, p);
            float w2 = edgeFunction(v0, v1, p);
            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                w0 /= area, w1 /= area, w2 /= area;
                float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
                float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
                float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
#ifdef PERSP_CORRECT
                float z = 1 / (w0 * v0[2] + w1 * v1[2] + w2 * v2[2]);
                // Multiply the result by z for perspective-correct interpolation
                r *= z, g *= z, b *= z;
#endif
                framebuffer[j * w + i][0] = static_cast<unsigned char>(r * 255);
                framebuffer[j * w + i][1] = static_cast<unsigned char>(g * 255);
                framebuffer[j * w + i][2] = static_cast<unsigned char>(b * 255);
            }
        }
    }
    
    std::ofstream ofs;
    ofs.open("./raster2d.ppm");
    ofs << "P6\n" << w << " " << h << "\n255\n";
    ofs.write(reinterpret_cast<char*>(framebuffer), w * h * 3);
    ofs.close();
    
    delete[] framebuffer;
    
    return 0;
}
