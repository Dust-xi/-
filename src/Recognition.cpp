#include "Recognition.h"
#include <QDebug>

Recognition::Recognition(QObject *parent) : QObject(parent)
{
    
}

cv::String Recognition::recogni(const QString &img)
{
    //std::cout << img.toStdString() << std::endl;
    cv::Mat image = cv::imread(img.toStdString());
    if(image.empty()){
        cerr << "not imag";
        exit(0);
    }
    
    //cv::Mat image = cv::imread("/home/du/project/intelligence_parking/res/test/A6666.png");
    //std::cout << "test_plate_recognize" << std::endl;
    
    easypr::CPlateRecognize pr;
    pr.setLifemode(true);
    pr.setDebug(false);
    pr.setMaxPlates(1);


    pr.LoadSVM("model/svm_hist.xml");
    pr.LoadANN("model/ann.xml");
    pr.LoadChineseANN("model/ann_chinese.xml");

    // new in v1.6
    pr.LoadGrayChANN("model/annCh.xml");
    pr.LoadChineseMapping("model/province_mapping");
    pr.setDetectType(easypr::PR_DETECT_CMSER);
    vector<easypr::CPlate> plateVec;

    int result = pr.plateRecognize(image, plateVec);
    if (result == 0) {
        size_t num = plateVec.size();
    for (size_t j = 0; j < num; j++) {
        //std::cout << "plateRecognize: " << plateVec[j].getPlateStr() << std::endl;
        return plateVec[j].getPlateStr();
    }
    }

    if (result != 0) {
        std::cout << "result:" << result << std::endl;
        return 0;
    }

}


Recognition::~Recognition()
{
}