#ifndef TILESETEDITORWINDOW_H
#define TILESETEDITORWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QStringListModel>

#include "tileset.h"


// Tileset Picker
class TilesetPicker : public QWidget
{
    Q_OBJECT
public:
    explicit TilesetPicker(QWidget *parent);
    void setTilesetImage(QImage *image);

signals:
    void selectedTileChanged(int x, int y);

public slots:

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;

private:
    QImage *tilesetImage;
    int selectedX;
    int selectedY;
};


namespace Ui {
class TilesetEditorWindow;
}

class TilesetEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TilesetEditorWindow(QWidget *parent, Tileset *tileset);
    ~TilesetEditorWindow();

public slots:
    void updateSelectedTile(int x, int y);

private slots:
    void on_hexLineEdit_textEdited(const QString &text);

    void on_actionExportImage_triggered();

    void on_sBehaviorListView_clicked(const QModelIndex &index);

    void on_parameterListView_clicked(const QModelIndex &index);

private:
    Ui::TilesetEditorWindow *ui;
    TilesetPicker* tilesetPicker;

    struct parameter
    {
        parameter(int byte, QString description) : byte(byte), description(description) {}
        int byte;
        QString description;
    };


    struct specialBehavior
    {
        int value;                      // Value of Byte 0
        QString description;            // Description of the SpecialBehavior
        QList<parameter> parameters;    // List of all used Parameters
    };

    Tileset* tileset;

    int selectedX;
    int selectedY;

    int selectedSpecialBehavior;
    int selectedParameter;

    QList<specialBehavior> specialBehaviors;

    void loadBehaviors();
    void updateHex();
    void updateBehavior();
    void setSBehaviorsModel();
    void setParametersModel();
};

#endif // TILESETEDITORWINDOW_H