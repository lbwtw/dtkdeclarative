// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "dquickitemscissor.h"
#include "dquickitemscissor_p.h"

DQUICK_BEGIN_NAMESPACE


DQuickItemScissor::DQuickItemScissor(QQuickItem *parent)
    : QQuickItem (parent)
    , DCORE_NAMESPACE::DObject(*new DQuickItemScissorPrivate(this))
{
    setFlag(ItemHasContents);
}

DQuickItemScissor::~DQuickItemScissor()
{

}

QQuickItem *DQuickItemScissor::source() const
{
    D_D(const DQuickItemScissor);
    return d->sourceItem;
}

void DQuickItemScissor::setSource(QQuickItem *item)
{
    D_D(DQuickItemScissor);

    if (d->sourceItem == item)
        return;

    if (isComponentComplete()) {
        d->initSourceItem(d->sourceItem, item);
    }

    d->sourceItem = item;
    d->markDirtys(DQuickItemScissorPrivate::DirtySourceSizeRatio
                  | DQuickItemScissorPrivate::DirtyMaskOffset);
    Q_EMIT sourceChanged();
    update();
}

qreal DQuickItemScissor::radius() const
{
    D_D(const DQuickItemScissor);
    return d->radius;
}

void DQuickItemScissor::setRadius(qreal radius)
{
    D_D(DQuickItemScissor);
    if (d->radius == radius)
        return;

    d->radius = radius;
    d->maybeSetImplicitAntialiasing();

    update();
    emit radiusChanged();

    if (d->extraRectangle.isAllocated()) {
        if (d->extraRectangle->topLeftRadius < 0.)
            emit topLeftRadiusChanged();
        if (d->extraRectangle->topRightRadius < 0.)
            emit topRightRadiusChanged();
        if (d->extraRectangle->bottomLeftRadius < 0.)
            emit bottomLeftRadiusChanged();
        if (d->extraRectangle->bottomRightRadius < 0.)
            emit bottomRightRadiusChanged();
    } else {
        emit topLeftRadiusChanged();
        emit topRightRadiusChanged();
        emit bottomLeftRadiusChanged();
        emit bottomRightRadiusChanged();
    }
}

qreal DQuickItemScissor::topLeftRadius() const
{
    D_D(const DQuickItemScissor);
    if (d->extraRectangle.isAllocated() && d->extraRectangle->topLeftRadius >= 0.)
        return d->extraRectangle.value().topLeftRadius;
    return d->radius;
}

void DQuickItemScissor::setTopLeftRadius(qreal radius)
{
    D_D(DQuickItemScissor);
    if (d->extraRectangle.value().topLeftRadius == radius)
        return;

    if (radius < 0) { // use the fact that radius < 0 resets the radius.
        qCWarning(DECLARATIVE_DTK) << "topLeftRadius (" << radius << ") cannot be less than 0.";
        return;
    }
    d->extraRectangle.value().topLeftRadius = radius;
    d->maybeSetImplicitAntialiasing();

    update();
    emit topLeftRadiusChanged();
}

void DQuickItemScissor::resetTopLeftRadius()
{
    D_D(DQuickItemScissor);
    if (!d->extraRectangle.isAllocated())
        return;
    if (d->extraRectangle.value().topLeftRadius < 0)
        return;

    d->extraRectangle.value().topLeftRadius = -1.;
    d->maybeSetImplicitAntialiasing();

    update();
    emit topLeftRadiusChanged();
}

qreal DQuickItemScissor::topRightRadius() const
{
    D_D(const DQuickItemScissor);
    if (d->extraRectangle.isAllocated()  && d->extraRectangle->topRightRadius >= 0.)
        return d->extraRectangle.value().topRightRadius;
    return d->radius;
}

void DQuickItemScissor::setTopRightRadius(qreal radius)
{
    D_D(DQuickItemScissor);
    if (d->extraRectangle.value().topRightRadius == radius)
        return;

    if (radius < 0) { // use the fact that radius < 0 resets the radius.
        qCWarning(DECLARATIVE_DTK) << "topRightRadius (" << radius << ") cannot be less than 0.";
        return;
    }
    d->extraRectangle.value().topRightRadius = radius;
    d->maybeSetImplicitAntialiasing();

    update();
    emit topRightRadiusChanged();
}

void DQuickItemScissor::resetTopRightRadius()
{
    D_D(DQuickItemScissor);
    if (!d->extraRectangle.isAllocated())
        return;
    if (d->extraRectangle.value().topRightRadius < 0)
        return;

    d->extraRectangle.value().topRightRadius = -1.;
    d->maybeSetImplicitAntialiasing();

    update();
    emit topRightRadiusChanged();
}

qreal DQuickItemScissor::bottomLeftRadius() const
{
    D_D(const DQuickItemScissor);
    if (d->extraRectangle.isAllocated() && d->extraRectangle->bottomLeftRadius >= 0.)
        return d->extraRectangle.value().bottomLeftRadius;
    return d->radius;
}

void DQuickItemScissor::setBottomLeftRadius(qreal radius)
{
    D_D(DQuickItemScissor);
    if (d->extraRectangle.value().bottomLeftRadius == radius)
        return;

    if (radius < 0) { // use the fact that radius < 0 resets the radius.
        qCWarning(DECLARATIVE_DTK) << "bottomLeftRadius (" << radius << ") cannot be less than 0.";
        return;
    }

    d->extraRectangle.value().bottomLeftRadius = radius;
    d->maybeSetImplicitAntialiasing();

    update();
    emit bottomLeftRadiusChanged();
}

void DQuickItemScissor::resetBottomLeftRadius()
{
    D_D(DQuickItemScissor);
    if (!d->extraRectangle.isAllocated())
        return;
    if (d->extraRectangle.value().bottomLeftRadius < 0)
        return;

    d->extraRectangle.value().bottomLeftRadius = -1.;
    d->maybeSetImplicitAntialiasing();

    update();
    emit bottomLeftRadiusChanged();
}

qreal DQuickItemScissor::bottomRightRadius() const
{
    D_D(const DQuickItemScissor);
    if (d->extraRectangle.isAllocated() && d->extraRectangle->bottomRightRadius >= 0.)
        return d->extraRectangle.value().bottomRightRadius;
    return d->radius;
}

void DQuickItemScissor::setBottomRightRadius(qreal radius)
{
    D_D(DQuickItemScissor);
    if (d->extraRectangle.value().bottomRightRadius == radius)
        return;

    if (radius < 0) { // use the fact that radius < 0 resets the radius.
        qCWarning(DECLARATIVE_DTK) << "bottomRightRadius (" << radius << ") cannot be less than 0.";
        return;
    }

    d->extraRectangle.value().bottomRightRadius = radius;
    d->maybeSetImplicitAntialiasing();

    update();
    emit bottomRightRadiusChanged();
}

void DQuickItemScissor::resetBottomRightRadius()
{
    D_D(DQuickItemScissor);
    if (!d->extraRectangle.isAllocated())
        return;
    if (d->extraRectangle.value().bottomRightRadius < 0)
        return;

    d->extraRectangle.value().bottomRightRadius = -1.;
    d->maybeSetImplicitAntialiasing();

    update();
    emit bottomRightRadiusChanged();
}

QSGNode *DQuickItemScissor::updatePaintNode(QSGNode *old, UpdatePaintNodeData *)
{
    return old;
}

void DQuickItemScissor::componentComplete()
{
    D_D(DQuickItemScissor);

    if (d->sourceItem)
        d->initSourceItem(nullptr, d->sourceItem);

    return QQuickItem::componentComplete();
}

void DQuickItemScissor::releaseResources()
{
    D_D(DQuickItemScissor);
    if (d->texture || d->provider) {
        window()->scheduleRenderJob(new DQuickItemScissorCleanup(d->texture, d->provider),
                                    QQuickWindow::AfterSynchronizingStage);
        d->texture = nullptr;
        d->provider = nullptr;
    }
}

QSGTextureProvider *DQuickItemScissor::sourceTextureProvider()
{
    D_D(DQuickItemScissor);

    if (!d->sourceItem)
        return nullptr;

    auto provider = d->sourceItem->textureProvider();
    if (provider)
        return provider;

    if (!d->provider) {
        d->provider = new DQuickViewportTextureProvider();
        d->ensureTexture();
        connect(d->texture, SIGNAL(updateRequested()), d->provider, SIGNAL(textureChanged()));
        d->provider->sourceTexture = d->texture;
    }

    return d->provider;
}

DQuickItemScissorPrivate::~DQuickItemScissorPrivate()
{

}

void DQuickItemScissorPrivate::ensureTexture()
{
    D_Q(DQuickItemScissor);
    if (texture)
        return;

    Q_ASSERT_X(QQuickItemPrivate::get(q)->window
                   && QQuickItemPrivate::get(q)->sceneGraphRenderContext()
                   && QThread::currentThread() == QQuickItemPrivate::get(q)->sceneGraphRenderContext()->thread(),
               "DQuickItemViewport",
               "Cannot be used outside the rendering thread");

    QSGRenderContext *rc = QQuickItemPrivate::get(q)->sceneGraphRenderContext();
    texture = rc->sceneGraphContext()->createLayer(rc);
    QObject::connect(QQuickItemPrivate::get(q)->window, SIGNAL(sceneGraphInvalidated()), texture, SLOT(invalidated()), Qt::DirectConnection);
    QObject::connect(texture, SIGNAL(updateRequested()), q, SLOT(update()));
}

void DQuickItemScissorPrivate::initSourceItem(QQuickItem *old, QQuickItem *item)
{
    if (old) {
        QQuickItemPrivate *sd = QQuickItemPrivate::get(old);
        sd->removeItemChangeListener(this, QQuickItemPrivate::Geometry);
        sd->derefFromEffectItem(hideSource);
    }

    if (textureChangedConnection)
        QObject::disconnect(textureChangedConnection);

    if (item) {
        QQuickItemPrivate *sd = QQuickItemPrivate::get(item);
        sd->addItemChangeListener(this, QQuickItemPrivate::Geometry);
        sd->refFromEffectItem(hideSource);
    }
}

void DQuickItemScissorPrivate::itemGeometryChanged(QQuickItem *item, QQuickGeometryChange data, const QRectF &)
{
    D_Q(DQuickItemScissor);

    if (data.sizeChange()) {
        markDirtys(DirtySourceSizeRatio | DirtyMaskOffset);
        q->update();
    }
}

void DQuickItemScissorPrivate::maybeSetImplicitAntialiasing()
{
    D_Q(DQuickItemScissor);
    bool implicitAA = (radius != 0);
    if (extraRectangle.isAllocated() && !implicitAA) {
        implicitAA = extraRectangle.value().topLeftRadius > 0.0
                     || extraRectangle.value().topRightRadius > 0.0
                     || extraRectangle.value().bottomLeftRadius > 0.0
                     || extraRectangle.value().bottomRightRadius > 0.0;
    }
    QQuickItemPrivate *item_d = static_cast<QQuickItemPrivate *>(QObjectPrivate::get(q));
    item_d->setImplicitAntialiasing(implicitAA);
}

DQUICK_END_NAMESPACE
