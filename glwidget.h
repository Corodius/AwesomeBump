/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

#include <QOpenGLFunctions>
#include "CommonObjects.h"
#include "camera.h"
#include <qmath.h>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);


//! [0]
class GLWidget : public QGLWidget , protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0 , QGLWidget * shareWidget  = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;    
    void setPointerToTexture(QGLFramebufferObject **pointer, TextureTypes type);

public slots:
    void setDepthScale(int scale);
    void setUVScale(int scale);

    void toggleDiffuseView(bool);
    void toggleSpecularView(bool);
    void toggleOcclusionView(bool);

    void setSpecularIntensity(double);
    void setDiffuseIntensity(double);
    void setUVScaleOffset(double x,double y);

signals:
    void rendered();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QPointF pixelPosToViewPos(const QPointF& p);
    int glhUnProjectf(float &winx, float &winy, float &winz,
                      QMatrix4x4 &modelview, QMatrix4x4 &projection,
                      QVector4D& objectCoordinate);
    void makeObject();
    QOpenGLShaderProgram *program;    
    QGLFramebufferObject**  fboIdPtrs[5];


    // parameters plane
    float depthScale;
    float uvScale;
    QVector2D uvOffset;
    float specularIntensity;
    float diffuseIntensity;
    bool bToggleDiffuseView;
    bool bToggleSpecularView;
    bool bToggleOcclusionView;

    // 3D view parameters
    GLuint vbos[3];
    GLuint no_triangles;
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 objectMatrix;
    QVector4D lightPosition;
    QVector4D cursorPositionOnPlane;
    float ratio;
    float zoom;
    QPoint lastPos;
    QMatrix4x4 RotatePlaneMatrix ;
    AwesomeCamera camera;
    QCursor lightCursor;
public:
};
//! [3]

#endif
