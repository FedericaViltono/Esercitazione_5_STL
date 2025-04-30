#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include <cmath>

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "File not found" << endl;
        return 1;
    }

    Gedim::UCDUtilities utilities;

    // Punti
    {   
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               cell0Ds_properties);
    }

    // Segmenti
    {
        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.MarkerCell1Ds)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {},
                                 cell1Ds_properties);
    }

    // Marker correttamente impostati
    cout << "Controllo marker dei punti:" << endl;
    for (const auto& coppia : mesh.MarkerCell0Ds) 
    {
        cout << coppia.first << ": ";
        for (const auto& element : coppia.second)
        {
            cout << element << " ";  
        }
        cout << '\n';
    }
    cout << std::endl; 

    cout << "Controllo marker dei segmenti:" << endl;
    for (const auto& coppia : mesh.MarkerCell1Ds) 
    {
        cout << coppia.first << ": ";
        for (const auto& element : coppia.second)
        {
            cout << element << " ";  
        }
        cout << '\n';
    }
    cout << std::endl; 

/*
    //cout << mesh.NumCell0Ds << endl;
    //cout << mesh.Cell0DsCoordinates << endl;

    cout << "CICLO PER SAPERE GLI ESTREMI" << endl;
    for (int i = 0; i < mesh.Cell1DsExtrema.rows(); ++i)
    {
        for (int j = 0; j < mesh.Cell1DsExtrema.cols(); ++j)
        {
            std::cout << mesh.Cell1DsExtrema(i, j) << " "; 
        }
        std::cout << std::endl; 
    }

    cout << "CICLO CHE UNISCE ID E COORDINATE" << endl;
    for (const auto& coppia : mesh.IdCoordCell0Ds) 
    {
        cout << coppia.first << ": ";
        for (const auto& element : coppia.second)
        {
            cout << element << " ";  
        }
        cout << '\n';
    }
*/

    // Lati con lunghezza non nulla
    cout << "Controllo lunghezza lati non nulla:" << endl;
    double epsilon = std::numeric_limits<double>::epsilon();
    bool check = true;

    for (int i = 0; i < mesh.Cell1DsExtrema.cols(); i+=2)
    {   
        unsigned int pt_inizio_id = mesh.Cell1DsExtrema(i);
        unsigned int pt_fine_id = mesh.Cell1DsExtrema(i+1);
        
        double x_inizio = mesh.IdCoordCell0Ds[pt_inizio_id][0];
        double y_inizio = mesh.IdCoordCell0Ds[pt_inizio_id][1];

        double x_fine = mesh.IdCoordCell0Ds[pt_fine_id][0];
        double y_fine = mesh.IdCoordCell0Ds[pt_fine_id][1];

        double distanza = sqrt((x_fine-x_inizio)*(x_fine-x_inizio) + (y_fine-y_inizio)*(y_fine-y_inizio));

        if (distanza < epsilon)
            cerr << "Il lato ha lunghezza nulla" << endl;
            check = false;
    }

    if (check = true)
        cout << "Tutti i lati hanno lunghezza non nulla" << endl;

    cout << std::endl; 


    // Poligoni con area non nulla
    //for (int i = 0; i < mesh.Cell1DsExtrema.cols(); i+=2)
/*
    // Memorizza id-coordinate
    const auto iss = mesh.IdPoligonoCell2Ds.find(id);
    if (iss == mesh.IdPoligonoCell2Ds.end())
    {
        mesh.IdPoligonoCell2Ds.insert({id, {      }});
    }
    else
    {
        it->second.push_back(id);
    }
*/







/*
    cout << "CELL2Ds" << endl;
    for (int i = 0; i < mesh.Cell2DsVertices.size(); i++)
    {
        for (int j = 0; j < mesh.Cell2DsVertices[i].size(); j++)
        {
            std::cout << mesh.Cell2DsVertices[i][j]} << " "; 
        }
        std::cout << std::endl; 
    }
    

    vector<unsigned int>& vec_vert = mesh.Cell2DsVertices[id];
    const unsigned int n = vec_vert.size();

    double area = 0.0;
    for(size_t i=0; i<n; i++)
    {   
        const unsigned int vi_id = vec_vert[i];
        const unsigned int vj_id = vec_vert[(i+1)%n]; //To close the polygon and connect the first vertice and the last vertice I use j=(i+1)%n

        const MatrixXd coord = mesh.Cell0DsCoordinates;
        const double X_vi = coord(0, vi_id);
        const double Y_vi = coord(1, vi_id);
        const double X_vj = coord(0, vj_id);
        const double Y_vj = coord(1, vj_id);

        area += (X_vi * Y_vj) - (X_vj * Y_vi);
    }
    area = abs(area / 2.0);

    if(area <= epsilon)
    {
        cerr<<"TEST NOT PASSED: the polygon  has area equal to zero";
        return false;
    }
    cout << area << endl;
*/
    return 0;
}

