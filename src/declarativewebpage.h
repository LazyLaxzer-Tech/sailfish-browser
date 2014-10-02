/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd.
** Contact: Raine Makelainen <raine.makelainen@jollamobile.com>
**
****************************************************************************/

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DECLARATIVEWEBPAGE_H
#define DECLARATIVEWEBPAGE_H

#include <qqml.h>
#include <QFutureWatcher>
#include <QQuickItemGrabResult>
#include <QPointer>
#include <quickmozview.h>

class DeclarativeWebContainer;

class DeclarativeWebPage : public QuickMozView {
    Q_OBJECT
    Q_PROPERTY(DeclarativeWebContainer* container READ container NOTIFY containerChanged FINAL)
    Q_PROPERTY(int tabId READ tabId FINAL)
    Q_PROPERTY(bool viewReady MEMBER m_viewReady NOTIFY viewReadyChanged FINAL)
    Q_PROPERTY(bool loaded MEMBER m_loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(bool userHasDraggedWhileLoading MEMBER m_userHasDraggedWhileLoading NOTIFY userHasDraggedWhileLoadingChanged FINAL)
    Q_PROPERTY(bool fullscreen READ fullscreen NOTIFY fullscreenChanged FINAL)
    Q_PROPERTY(bool domContentLoaded READ domContentLoaded NOTIFY domContentLoadedChanged FINAL)
    Q_PROPERTY(QString favicon MEMBER m_favicon NOTIFY faviconChanged FINAL)
    Q_PROPERTY(QVariant resurrectedContentRect READ resurrectedContentRect WRITE setResurrectedContentRect NOTIFY resurrectedContentRectChanged)

public:
    DeclarativeWebPage(QQuickItem *parent = 0);
    ~DeclarativeWebPage();

    DeclarativeWebContainer* container() const;
    void setContainer(DeclarativeWebContainer *container);

    int tabId() const;
    void setTabId(int tabId);

    QVariant resurrectedContentRect() const;
    void setResurrectedContentRect(QVariant resurrectedContentRect);

    bool fullscreen() const;
    bool domContentLoaded() const;

    bool urlHasChanged() const;
    void setUrlHasChanged(bool urlHasChanged);

    bool backForwardNavigation() const;
    void setBackForwardNavigation(bool backForwardNavigation);

    bool viewReady() const;

    Q_INVOKABLE void loadTab(QString newUrl, bool force);
    Q_INVOKABLE void grabToFile();
    Q_INVOKABLE void grabThumbnail();

signals:
    void containerChanged();
    void viewReadyChanged();
    void loadedChanged();
    void userHasDraggedWhileLoadingChanged();
    void fullscreenChanged();
    void domContentLoadedChanged();
    void faviconChanged();
    void resurrectedContentRectChanged();
    void clearGrabResult();
    void grabResult(QString fileName);
    void thumbnailResult(QString data);

protected:
    void componentComplete();

private slots:
    void setFullscreen(const bool fullscreen);
    void onRecvAsyncMessage(const QString& message, const QVariant& data);
    void onViewInitialized();
    void grabResultReady();
    void grabWritten();
    void thumbnailReady();

private:
    QString saveToFile(QImage image, QRect cropBounds);

    QPointer<DeclarativeWebContainer> m_container;
    int m_tabId;
    bool m_viewReady;
    bool m_loaded;
    bool m_userHasDraggedWhileLoading;
    bool m_fullscreen;
    bool m_domContentLoaded;
    bool m_urlHasChanged;
    bool m_backForwardNavigation;
    QString m_favicon;
    QVariant m_resurrectedContentRect;
    QSharedPointer<QQuickItemGrabResult> m_grabResult;
    QSharedPointer<QQuickItemGrabResult> m_thumbnailResult;
    QFutureWatcher<QString> m_grabWritter;
};

QDebug operator<<(QDebug, const DeclarativeWebPage *);

QML_DECLARE_TYPE(DeclarativeWebPage)

#endif
