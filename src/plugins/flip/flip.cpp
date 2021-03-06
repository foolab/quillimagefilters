/****************************************************************************
**
** Copyright (C) 2009-11 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Pekka Marjola <pekka.marjola@nokia.com>
**
** This file is part of the Quill Image Filters package.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include <QImage>

#include "quillimagefilter.h"
#include "flip.h"



class FlipPrivate
{
public:
    bool horizontal;
};

Flip::Flip()
{
    priv = new FlipPrivate;
    priv->horizontal = false;
}

Flip::~Flip()
{
    delete priv;
}

QuillImage Flip::apply(const QuillImage &image) const
{
    QuillImage result;

    if (!priv->horizontal)
        result = image.transformed(QTransform().scale(1, -1));
    else
        result = image.transformed(QTransform().scale(-1, 1));

    result.setFullImageSize(newFullImageSize(image.fullImageSize()));
    result.setArea(newArea(image.fullImageSize(), image.area()));

    return result;
}

QRect Flip::newArea(const QSize &fullImageSize, const QRect &area) const
{
    if (!priv->horizontal)
       return QRect(area.left(), fullImageSize.height() - area.bottom() - 1,
                     area.width(), area.height());
    else
        return QRect(fullImageSize.width() - area.right() - 1, area.top(),
                     area.width(), area.height());
}

bool Flip::setOption(const QString &option, const QVariant &value)
{
    bool bOK = true;

    if (option == QuillImageFilter::Horizontal)
        priv->horizontal = value.toBool();
    else
        bOK = false;

    return bOK;
}

QVariant Flip::option(const QString &option) const
{
    if (option == QuillImageFilter::Horizontal)
        return QVariant(priv->horizontal);
    else
        return QVariant();
}

const QStringList Flip::supportedOptions() const
{
    return QStringList() << QuillImageFilter::Horizontal;
}

