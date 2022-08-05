#include <QCoreApplication>
#include <QCommandLineParser>
#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <iostream>
#include "pathtracer.h"
#include "scene/scene.h"
#include <QImage>
#include "util/CS123Common.h"
#include "ui/MyWidget.h"
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <thread>
#include <QBuffer>





int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument("scene", "Scene file to be rendered");
    parser.addPositionalArgument("output", "Image file to write the rendered image to");
    parser.process(a);


    const QStringList args = parser.positionalArguments();
    if(args.size() != 2) {
        std::cerr << "Error: Wrong number of arguments" << std::endl;
        a.exit(1);
        return 1;
    }
    QString scenefile = args[0];
    QString output = args[1];

    QImage image(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format_RGB32);

    Scene *scene;
    if(!Scene::load(scenefile, &scene)) {
        std::cerr << "Error parsing scene file " << scenefile.toStdString() << std::endl;
        a.exit(1);
        return 1;
    }


    PathTracer tracer(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_HEIGHT, 0, "");

    QRgb *data = reinterpret_cast<QRgb *>(image.bits());
//    QRgb *composite = reinterpret_cast<QRgb *>(image.bits());


    MyWidget widget(NULL, &a);  // create a widget
    widget.show();  //show the widget and its children

//    QString s = "";
//    QImage endIMG = QImage(s);

    //bool jesus = true;
    //while(true)
    //{




        tracer.traceScene(data, *scene, &widget);
        bool success = image.save(output);
        if(!success) {
            success = image.save(output, "PNG");
        }
        if(success) {
            std::cout << "Wrote rendered image to " << output.toStdString() << std::endl;
        } else {
            std::cerr << "Error: failed to write image to " << output.toStdString() << std::endl;
        }





//        for(int y = 0; y < IMAGE_HEIGHT; ++y) {
//            for(int x = 0; x < IMAGE_WIDTH; ++x) {
//                int offset = x + (y * IMAGE_WIDTH);

//                if(jesus)
//                {
//                    composite[offset] = data[offset];
//                    jesus = false;
//                }


//                composite[offset] += data[offset];
//                composite[offset] = composite[offset]/2;

//                data[offset] = composite[offset];
//            }
//        }
        //widget.scene_TO_DRAW->addPixmap(composite);
        //widget.scene_TO_DRAW->addPixmap(output);



        a.processEvents();
    //}
    delete scene;


    return a.exec(); // execute the application
}
