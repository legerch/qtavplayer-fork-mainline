/*********************************************************
 * Copyright (C) 2020, Val Doroshchuk <valbok@gmail.com> *
 *                                                       *
 * This file is part of QtAVPlayer.                      *
 * Free Qt Media Player based on FFmpeg.                 *
 *********************************************************/

#include "qavhwdevice_mediacodec_p.h"
#include "qavvideocodec_p.h"
#include "qavplanarvideobuffer_gpu_p.h"
#include <QVideoFrame>
#include <QDebug>

extern "C" {
#include <libavutil/pixdesc.h>
}

QT_BEGIN_NAMESPACE

QAVHWDevice_MediaCodec::QAVHWDevice_MediaCodec(QObject *parent)
    : QObject(parent)
{
}

AVPixelFormat QAVHWDevice_MediaCodec::format() const
{
    return AV_PIX_FMT_MEDIACODEC;
}

AVHWDeviceType QAVHWDevice_MediaCodec::type() const
{
    return AV_HWDEVICE_TYPE_MEDIACODEC;
}

bool QAVHWDevice_MediaCodec::supportsVideoSurface(QAbstractVideoSurface *surface) const
{
    if (!surface)
        return false;

    auto list = surface->supportedPixelFormats(QAbstractVideoBuffer::NoHandle);
    return list.contains(QVideoFrame::Format_NV12);
}

QVideoFrame QAVHWDevice_MediaCodec::decode(const QAVVideoFrame &frame) const
{
    return {new QAVPlanarVideoBuffer_CPU(frame), frame.size(), QVideoFrame::Format_NV12};
}

QT_END_NAMESPACE
