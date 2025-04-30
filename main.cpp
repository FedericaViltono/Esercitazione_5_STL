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

    // Lati con lunghezza non nulla
    cout << "Controllo lunghezza lati non nulla:" << endl;
    double epsilon = std::numeric_limits<double>::epsilon();
    bool check_lunghezza = true;

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
            check_lunghezza = false;
    }

    if (check_lunghezza = true)
        cout << "Tutti i lati hanno lunghezza non nulla" << endl;

    cout << std::endl; 

    // Poligoni con area non nulla
    cout << "Controllo area poligoni non nulla:" << endl;
    bool check_area = true;
    for (unsigned int i = 0; i < mesh.Cell2DsVertices.size(); i++)
    {
        double area = 0.0; 

        for (unsigned int j = 0; j < mesh.Cell2DsVertices[i].size(); j++)
        {
            unsigned int chiave = mesh.Cell2DsVertices[i][j];
            if (mesh.IdCoordCell0Ds.find(chiave) != mesh.IdCoordCell0Ds.end()) 
            {
                double x = mesh.IdCoordCell0Ds[chiave][0];
                double y = mesh.IdCoordCell0Ds[chiave][1];

                unsigned int nextIndex = (j + 1) % mesh.Cell2DsVertices[i].size(); // Indice del vertice successivo: j + 1 prende l'elemento successivo e % size fa in modo che quando j è l'ultimo indice, torni a 0
                unsigned int nextChiave = mesh.Cell2DsVertices[i][nextIndex];
                double nextX = mesh.IdCoordCell0Ds[nextChiave][0];
                double nextY = mesh.IdCoordCell0Ds[nextChiave][1];

                area += (x * nextY - nextX * y);
            } 
        }

        area = std::abs(area) * 0.5; 

        if (area < epsilon)
            cerr << "Il poligono ha area nulla" << endl;
            check_area = false;
    }

    if (check_area = true)
    cout << "Tutti i poligoni hanno area non nulla" << endl;

    return 0;
}

