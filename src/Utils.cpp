#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}

// ***************************************************************************

bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if (file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // Rimuove la prima riga 
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "Non ci sono celle 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds); 

    for (const string& line : listLines)
    {
        istringstream converter(line);
        string temp;

        unsigned int id;
        unsigned int marker;
        Eigen::Vector2d coord;

        // Id
        getline(converter, temp, ';');
        istringstream(temp) >> id;

        // Marker
        getline(converter, temp, ';');
        istringstream(temp) >> marker;

        // X
        getline(converter, temp, ';');
        istringstream(temp) >> coord(0); 

        // Y
        getline(converter, temp, ';');
        istringstream(temp) >> coord(1); 

        // Salva i dati
        mesh.Cell0DsId.push_back(id);
        mesh.Cell0DsCoordinates(0, id) = coord(0);
        mesh.Cell0DsCoordinates(1, id) = coord(1);

        // Memorizza i marker
        if (marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if (it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }

        // Memorizza id-coordinate
        const auto is = mesh.IdCoordCell0Ds.find(id);
        if (is == mesh.IdCoordCell0Ds.end())
            {
                mesh.IdCoordCell0Ds.insert({id, {coord(0), coord(1)}});
            }
    }

    return true;
}

// ***************************************************************************

bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if (file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // Rimuove la prima riga
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "Non ci sono celle 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);
        string temp;

        unsigned int id;
        unsigned int marker;
        Eigen::Vector2i vertices;

        // Id
        getline(converter, temp, ';');
        istringstream(temp) >> id;

        // Marker
        getline(converter, temp, ';');
        istringstream(temp) >> marker;

        // Origin
        getline(converter, temp, ';');
        istringstream(temp) >> vertices(0);

        // End
        getline(converter, temp, ';');
        istringstream(temp) >> vertices(1);

        // Salva i dati
        mesh.Cell1DsId.push_back(id);
        mesh.Cell1DsExtrema(0, id) = vertices(0);
        mesh.Cell1DsExtrema(1, id) = vertices(1);

        // Memorizza i marker
        if (marker != 0)
        {
            auto it = mesh.MarkerCell1Ds.find(marker);
            if (it == mesh.MarkerCell1Ds.end())
            {
                mesh.MarkerCell1Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }
    }
    return true;
}

// ***************************************************************************

bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // Rimuove la prima riga
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "Non ci sono celle 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);
        string temp;

        unsigned int id;
        unsigned int marker;
        unsigned int num_vertices;

        // Id
        getline(converter, temp, ';');
        istringstream(temp) >> id;

        // Marker
        getline(converter, temp, ';');
        istringstream(temp) >> marker;

        // Numero vertici
        getline(converter, temp, ';');
        istringstream(temp) >> num_vertices;

        std::vector<unsigned int> vertices(num_vertices);
        std::vector<unsigned int> edges(num_vertices);

        // Vertici
        for(unsigned int i = 0; i < num_vertices; ++i)
        {
            getline(converter, temp, ';');
            istringstream(temp) >> vertices[i];
        }

        // Lati
        for(unsigned int i = 0; i < num_vertices; ++i)
        {
            getline(converter, temp, ';');
            istringstream(temp) >> edges[i];
        }

        // Salva i dati
        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);

        // Memorizza i marker
        if (marker != 0)
        {
            auto it = mesh.MarkerCell2Ds.find(marker);
            if (it == mesh.MarkerCell2Ds.end())
            {
                mesh.MarkerCell2Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }
    }
}

}