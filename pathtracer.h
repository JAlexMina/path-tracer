#ifndef PATHTRACER_H
#define PATHTRACER_H

#include <QImage>

#include "scene/scene.h"
#include "bsdf.h"
#include "util/pathnode.h"
#include "util/sampleinfo.h"
#include "ui/MyWidget.h"

enum RenderType {
    PATH_TRACING,
    BIDIRECTIONAL
};

class PathTracer
{
public:
    PathTracer(int width, int image_height, int output_height, int section_id, QString name);
    void traceScene(QRgb *imageData, const Scene &scene, MyWidget* mw);
    void tracePixelPT(int pixel_x, int pixel_y, const Scene& scene,
                    PixelInfo *pixelInfo, const Eigen::Matrix4f &invViewMatrix);
    void tracePixelBD(int output_x, int output_y, const Scene& scene,
                     PixelInfo *pixelInfo, const Eigen::Matrix4f &invViewMatrix);

    void updateUI(MyWidget* mw, QRgb *imageData, PixelInfo *pixelInfo);


    static float getContinueProbability(Eigen::Vector3f brdf);

private:

    int m_width, m_image_height, m_output_height, m_section_id;

    QString m_name;


    /* Adjust the number of samples for each pixel (N in equations) */
    const int M_NUM_SAMPLES = 1000;

    /* Helpers for parallelism and logging */
    bool should_run_parallel = false;
    const int PARALLEL_RANGE = 20;

    /* Indicates if image should be denoised or tone-mapped */
    bool should_denoise = true;
    bool use_direct_lighting = true;

    //const RenderType render_type = BIDIRECTIONAL; // PATH_TRACING is the other option
    const RenderType render_type = PATH_TRACING; // BIDIRECTIONAL is the other option

    void toneMap(QRgb *imageData, PixelInfo *pixelInfo);

    Eigen::Vector3f traceRay(const Ray& r, const Scene &scene, int depth);
    bool lightIsVisible(Eigen::Vector3f light_position, Eigen::Vector3f surface_position, const Scene& scene);
    Eigen::Vector3f directLightContribution(SampledLightInfo light_info, Eigen::Vector3f surface_normal, MaterialType type,
                                            Eigen::Vector3f surface_position, Ray incoming_ray, const tinyobj::material_t& mat);

    Eigen::Vector3f directLightContributionSingleScattering(SampledLightInfo light_info, Eigen::Vector3f surface_normal, MaterialType type,
                                            Eigen::Vector3f surface_position, Ray incoming_ray, const tinyobj::material_t& mat);

    Eigen::Vector3f directLightContributionScattering(SampledLightInfo light_info, Eigen::Vector3f surface_normal, MaterialType type,
                                            Eigen::Vector3f surface_position, Ray incoming_ray, const tinyobj::material_t& mat, const Scene &scene);

    void tracePath(const Ray& ray, const Scene& scene, int depth, std::vector<PathNode> &nodes, const Eigen::Vector3f &prev_brdf, bool &noScattering);
 };

#endif // PATHTRACER_H
