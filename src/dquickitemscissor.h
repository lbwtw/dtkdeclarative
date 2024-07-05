// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DQUICKITEMSCISSOR_H
#define DQUICKITEMSCISSOR_H

#include <dtkdeclarative_global.h>
#include <DObject>

#include <QQuickItem>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QPainter>
#endif

DQUICK_BEGIN_NAMESPACE

class DQuickItemScissorPrivate;
class DQuickItemScissor : public QQuickItem, public DCORE_NAMESPACE::DObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(qreal topLeftRadius READ topLeftRadius WRITE setTopLeftRadius NOTIFY topLeftRadiusChanged RESET resetTopLeftRadius FINAL)
    Q_PROPERTY(qreal topRightRadius READ topRightRadius WRITE setTopRightRadius NOTIFY topRightRadiusChanged RESET resetTopRightRadius FINAL)
    Q_PROPERTY(qreal bottomLeftRadius READ bottomLeftRadius WRITE setBottomLeftRadius NOTIFY bottomLeftRadiusChanged RESET resetBottomLeftRadius FINAL)
    Q_PROPERTY(qreal bottomRightRadius READ bottomRightRadius WRITE setBottomRightRadius NOTIFY bottomRightRadiusChanged RESET resetBottomRightRadius FINAL)
    D_DECLARE_PRIVATE(DQuickItemScissor)
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QML_NAMED_ELEMENT(DItemScissor)
#endif

public:
    explicit DQuickItemScissor(QQuickItem *parent = nullptr);
    ~DQuickItemScissor() override;

    QQuickItem *source() const;
    void setSource(QQuickItem *item);

    qreal radius() const;
    void setRadius(qreal radius);

    qreal topLeftRadius() const;
    void setTopLeftRadius(qreal radius);
    void resetTopLeftRadius();
    qreal topRightRadius() const;
    void setTopRightRadius(qreal radius);
    void resetTopRightRadius();
    qreal bottomLeftRadius() const;
    void setBottomLeftRadius(qreal radius);
    void resetBottomLeftRadius();
    qreal bottomRightRadius() const;
    void setBottomRightRadius(qreal radius);
    void resetBottomRightRadius();

Q_SIGNALS:
    void sourceChanged();
    void radiusChanged();
    void topLeftRadiusChanged();
    void topRightRadiusChanged();
    void bottomLeftRadiusChanged();
    void bottomRightRadiusChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *old, UpdatePaintNodeData *) override;
    void componentComplete() override;
    void releaseResources() override;

private:
    QSGTextureProvider *sourceTextureProvider();
};

DQUICK_END_NAMESPACE

#endif // DQUICKITEMSCISSOR_H
