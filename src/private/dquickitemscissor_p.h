// SPDX-FileCopyrightText: 2024 - 2025 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DQUICKITEMSCISSOR_P_H
#define DQUICKITEMSCISSOR_P_H

#include "dquickitemscissor.h"
#include "dquickitemviewport_p.h"

#include <DObjectPrivate>

#include <private/qquickitem_p.h>

#include <QRunnable>

DQUICK_BEGIN_NAMESPACE

class Q_DECL_HIDDEN DQuickItemScissorCleanup : public QRunnable
{
public:
    DQuickItemScissorCleanup(QSGLayer *texture,
                          DQuickViewportTextureProvider *provider)
        : texture(texture)
        , provider(provider)
    {}
    void run() override {
        delete texture;
        delete provider;
    }
    QSGLayer *texture;
    DQuickViewportTextureProvider *provider;
};

class Q_DECL_HIDDEN DQuickItemScissorPrivate : public DCORE_NAMESPACE::DObjectPrivate, public QQuickItemChangeListener
{
public:
    enum DirtyStateBit {
        DirtyNothing = 0x0,
        DirtySourceSizeRatio = 0x1,
        DirtyMaskTexture = 0x2,
        DirtyMaskSizeRatio = 0x4,
        DirtyMaskOffset = 0x8,
        DirtyContentNode = 0x10
    };
    Q_DECLARE_FLAGS(DirtyState, DirtyStateBit)

    DQuickItemScissorPrivate(DQuickItemScissor *qq)
        : DObjectPrivate(qq)
    {

    }

    ~DQuickItemScissorPrivate() override;

    inline void markDirtys(DirtyState states) {
        dirtyState |= states;
    }
    inline void markDirty(DirtyStateBit state, bool dirty = true) {
        if (dirty) {
            dirtyState |= state;
        } else {
            dirtyState &= ~state;
        }
    }

    void ensureTexture();
    void maybeSetImplicitAntialiasing();
    void initSourceItem(QQuickItem *old, QQuickItem *item);
    void itemGeometryChanged(QQuickItem *item, QQuickGeometryChange data, const QRectF &) override;

    D_DECLARE_PUBLIC(DQuickItemScissor)

    QPointer<QQuickItem> sourceItem;
    qreal radius;
    struct ExtraData {
        ExtraData()
            : topLeftRadius(-1.),
            topRightRadius(-1.),
            bottomLeftRadius(-1.),
            bottomRightRadius(-1.)
        {
        }

        qreal topLeftRadius;
        qreal topRightRadius;
        qreal bottomLeftRadius;
        qreal bottomRightRadius;
    };
    QLazilyAllocated<ExtraData> extraRectangle;
    DirtyState dirtyState = DirtyNothing;
    QMetaObject::Connection textureChangedConnection;
    bool hideSource = false;
    QSGLayer *texture = nullptr;
    DQuickViewportTextureProvider *provider = nullptr;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(DQuickItemScissorPrivate::DirtyState)
DQUICK_END_NAMESPACE
#endif // DQUICKITEMSCISSOR_P_H
