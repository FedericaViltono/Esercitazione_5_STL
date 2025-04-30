#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{   
    // Punti
    unsigned int NumCell0Ds = 0; 
    std::vector<unsigned int> Cell0DsId = {}; 
    Eigen::MatrixXd Cell0DsCoordinates = {}; 
    std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {};
    std::map<unsigned int, vector<double>> IdCoordCell0Ds = {}; 

    // Segmenti
    unsigned int NumCell1Ds = 0; 
    std::vector<unsigned int> Cell1DsId = {};
    Eigen::MatrixXi Cell1DsExtrema = {};
    std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; 

    // Poligoni
    unsigned int NumCell2Ds = 0; 
    std::vector<unsigned int> Cell2DsId = {};
    std::vector<vector<unsigned int>> Cell2DsVertices = {}; 
    std::vector<vector<unsigned int>> Cell2DsEdges = {};
    std::map<unsigned int, list<unsigned int>> MarkerCell2Ds = {};
};

}




