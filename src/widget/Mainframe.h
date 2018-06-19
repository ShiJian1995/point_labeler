#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <stdint.h>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QMainWindow>
#include <future>
#include "KittiReader.h"
#include "LabelButton.h"
#include "common.h"
#include "data/geometry.h"
#include "data/transform.h"
#include "ui_MainFrame.h"
#include "waitingspinnerwidget.h"

// TODO: undo.

/** \brief main widget showing the point cloud and tools to label a point cloud/multiple point clouds. **/
class Mainframe : public QMainWindow {
  Q_OBJECT
 public:
  Mainframe();
  ~Mainframe();

 public slots:
  void open();
  void save();
  void changeRadius(int radius);
  void changeMode(int mode);

  void updateFiltering(bool value);
  void labelBtnReleased(QWidget*);

 signals:
  void readerStarted();
  void readerFinshed();

 protected:
  void readAsync(uint32_t i, uint32_t j);

  void updateScans();
  void activateSpinner();

  void forward();
  void backward();

  void setTileIndex(uint32_t i, uint32_t j);

  void setCurrentScanIdx(int32_t idx);

  void generateLabelButtons();
  void closeEvent(QCloseEvent* event);

  void readConfig();

  std::vector<uint32_t> indexes_;
  std::vector<PointcloudPtr> points_;
  std::vector<LabelsPtr> labels_;

  std::vector<uint32_t> filteredLabels;
  std::string filename;

  void keyPressEvent(QKeyEvent* event);

 protected slots:
  void unsavedChanges();

 private:
  Ui::MainWindow ui;
  QSignalMapper* labelButtonMapper;
  std::vector<LabelButton*> labelButtons;
  std::map<LabelButton*, uint32_t> labelIds;
  std::map<int32_t, uint32_t> idxLabelMap;
  std::map<uint32_t, int32_t> labelIdxMap;
  bool mChangesSinceLastSave;
  QString lastDirectory;

  Point3f midpoint;

  KittiReader reader_;
  std::future<void> readerFuture_;
  WaitingSpinnerWidget* spinner{nullptr};
};

#endif /* MAINFRAME_H_ */
