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
    options.frames_to_generate = ui->interpFrames->value();
    options.mv_correction_algorithm = Algorithm::odd_mv_corrector;
    options.opt_flow_algorithm = Algorithm::diamond_search;
    options.smooth_edges = false;
    options.max_valid_cost = 75;

    if (ui->inputFile->text().length() == 0)
        return;

    Interpolator interpolator;
    interpolator.set_input_file_name(ui->inputFile->text().toStdString());
    interpolator.set_output_file_name(ui->outputFile->text().toStdString());

    interpolator.options() = options;
    interpolator.set_progress_callback([&](double progress)
    {
        ui->progressBar->setValue(100 * progress + 1);
    });
    interpolator.run();
    interpolator.save_video();
}

void MainWindow::on_chooseButton_clicked()
{
    QString input_file = QFileDialog::getOpenFileName(this, "Open video file", "", "All files (*.*)");
    if (input_file.length() == 0)
        return;
    ui->inputFile->setText(input_file);
    QString output_file = QFileInfo(ui->inputFile->text()).dir().absolutePath() + "/video.avi";
    ui->outputFile->setText(output_file);
}
