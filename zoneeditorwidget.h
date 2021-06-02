#ifndef ZONEEDITORWIDGET_H
#define ZONEEDITORWIDGET_H

#include "objects.h"
#include "settingsmanager.h"

#include <QWidget>
#include <QListWidget>
#include <QFrame>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QScrollArea>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>
#include <QGroupBox>

class BgPreview : public QLabel
{
    Q_OBJECT
public:
    BgPreview();
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
    void setBg(QPixmap bg);
private:
    QPixmap bg;
};

class ZoneBackgroundWidget : public QDialog
{
    Q_OBJECT
public:
    ZoneBackgroundWidget(QList<ZoneBackground*> *backgrounds);
    void updateWidget();
    void setSelectedIndex(int index);

signals:
    void editMade();
    void selectedBackgroundChanged(int val);

private:
    void loadBackgrounds();

    void updateBgPreview();

    QListWidget* backgroundList;

    QPushButton* addBackgroundBtn;
    QPushButton* removeBackgroundBtn;

    QGroupBox* settingsGroup;
    QSpinBox* backgroundId;
    QComboBox* background;
    QMap<QString, QString> backgrounds;
    BgPreview* backgroundPreview;
    QSpinBox* xPos;
    QSpinBox* yPos;
    QComboBox* parallaxMode;

    QList<ZoneBackground*> *zoneBgs;
    ZoneBackground* editBg;

    void updateList();
    void updateInfo();

    bool editingABg = false;
    bool handleChanges = true;

private slots:
    void handleBackgroundListIndexChange(QListWidgetItem* item);
    void handleBackgroundListDoubleClick(QListWidgetItem* item);
    void handleBackgroundChange(QString text);
    void handleParallaxModeChange(int val);
    void handleXPosChanged(int val);
    void handleYPosChanged(int val);
    void handleBackgroundIDChanged(int val);
    void handleAddBackgroundClicked();
    void handleRemoveBackgroundClicked();
};

class ZoneBoundingWidget : public QDialog
{
    Q_OBJECT
public:
    ZoneBoundingWidget(QList<ZoneBounding*> *boundings);
    void updateWidget();
    void setSelectedIndex(int index);

signals:
    void editMade();
    void selectedBoundingChanged(int val);

private:
    QListWidget* boundingList;

    QPushButton* addBoundingBtn;
    QPushButton* removeBoundingBtn;

    QGroupBox* settingsGroup;
    QSpinBox* boundingId;
    QSpinBox* primaryUpperBound;
    QSpinBox* primaryLowerBound;
    QSpinBox* secondaryUpperBound;
    QSpinBox* secondaryLowerBound;
    QCheckBox* unlimitedScrolling;
    QSpinBox* vertScrollingDistance;

    QList<ZoneBounding*> *zoneBoundings;
    ZoneBounding* editBounding;

    void updateList();
    void updateInfo();

    bool editingABounding = false;
    bool handleChanges = true;

private slots:
    void handleBoundingListIndexChange(QListWidgetItem* item);
    void handleBoundingListDoubleClick(QListWidgetItem* item);
    void handleUnlimitedScrollingChange(bool val);
    void handleVertScrollingDistanceChange(int val);
    void handlePrimaryUpperBoundChange(int val);
    void handlePrimaryLowerBoundChange(int val);
    void handleSecondaryUpperBoundChange(int val);
    void handleSecondaryLowerBoundChange(int val);
    void handleAddBoundingClicked();
    void handleRemoveBoundingClicked();
    void handleBoundingIdChange(int val);
};

class ZoneEditorWidget : public QWidget
{
    Q_OBJECT
public:
    ZoneEditorWidget(QList<Zone*> *zones, QList<ZoneBackground*> *bgs, QList<ZoneBounding*> *bounds);
    ~ZoneEditorWidget();
    void deselect();
    void select(Zone* zone);
    void updateEditor();

signals:
    void updateLevelView();
    void selectedZoneChanged(Object* zone);
    void selectZoneContents(Zone* zone);
    void editMade();
    void screenshot(QRect);

private:
    QListWidget* zoneList;

    QPushButton* selectContentsBtn;
    QPushButton* screenshotBtn;

    QSpinBox* id;
    QComboBox* multiplayerTracking;
    QMap<int, QString> multiplayerTrackings;
    QSpinBox* progPathId;
    QComboBox* musicId;
    QMap<int, QPair<int, QString>> musicIds;
    QSpinBox* unk1;

    QSpinBox* boundingId;
    QPushButton* editBounding;
    ZoneBoundingWidget* boundingWidget;

    QSpinBox* backgroundId;
    QPushButton* editBackground;
    ZoneBackgroundWidget* backgroundWidget;

    QGroupBox* settingsGroup;

    QList<Zone*> *zones;
    QList<ZoneBounding*> *zoneBoundings;
    QList<ZoneBackground*> *zoneBgs;
    Zone* editZone;

    void changeEvent(QEvent* event);

    void loadMusicIDs();

    void updateList();
    void updateInfo();

    bool editingAZone = false;
    bool handleChanges = true;

private slots:
    void handleZoneListIndexChange(QListWidgetItem* item);
    void handleIDChange(int idVal);
    void handleProgPathIDChange(int ppIDVal);
    void handleMusicIDChange(QString text);
    void handleMultiPlayerTrackingChange(QString text);
    void handleUnk1Change(int val);
    void handleSelectContentsClicked();
    void handleScreenshotClicked();
    void handleBoundingIDChange(int val);
    void handleBackgroundIDChange(int val);
    void handleEditBoundingClicked();
    void handleEditBackgroundClicked();
    void handleEditMade();
};

#endif // ZONEEDITORWIDGET_H
