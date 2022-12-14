#include "renderthread.h"

#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>

#include "pathtracer.h"


using namespace Eigen;

void RenderThread::run()
{
    /* Now that we have a new thread, we can tell the scene to render itself. */
    for (int x = 0; x < m_range; x ++) {
        for (int y = 0; y < m_range; y++) {
            switch (m_render_type) {
            case PATH_TRACING:
                m_pathTracer->tracePixelPT(m_x + x, m_y + y, m_scene, m_pixelInfo, *m_invViewMatrix);
                break;
            case BIDIRECTIONAL:
                m_pathTracer->tracePixelBD(m_x + x, m_y + y, m_scene, m_pixelInfo, *m_invViewMatrix);
            }
        }

        m_pathTracer->updateUI(mw, imageData, m_pixelInfo);
    }

}

void RenderThread::setData(PathTracer *p,  PixelInfo *pixelInfo, const Scene &scene, int x, int y,
                           int range, Matrix4f *invViewMatrix, RenderType render_type) {
    m_pathTracer = p;
    m_pixelInfo = pixelInfo;
    m_scene = scene;
    m_x = x;
    m_y = y;
    m_range = range;
    m_invViewMatrix = invViewMatrix;
    m_render_type = render_type;
}
