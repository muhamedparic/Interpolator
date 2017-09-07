#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "test/test_diamond_search.h"
#include "interpolator.h"
#include "interpolator_options.h"
#include "algorithm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    Interpolator_options options;
    options.block_size = 16;
    options.blur_overlaps = true;
    options.fix_holes = true;
    options.frames_to_generate = 1;
    options.mv_correction_algorithm = Algorithm::odd_mv_corrector;
    options.opt_flow_algorithm = Algorithm::diamond_search;
    options.smooth_edges = false;
    options.max_valid_cost = 75;

    // Temporary!
    std::string input_file = QFileDialog::getOpenFileName(this, "Open video file", "/home/muhamed/Desktop/videos", "All files (*.*)").toStdString();
    std::string output_file = "/home/muhamed/Desktop/Videos/video.avi";

    Interpolator interpolator;
    interpolator.set_input_file_name(input_file);
    interpolator.set_output_file_name(output_file);

    interpolator.options() = options;
    interpolator.set_progress_callback([&](double progress)
    {
        ui->progressBar->setValue(100 * progress);
    });
    interpolator.run();
    interpolator.save_video();
}
