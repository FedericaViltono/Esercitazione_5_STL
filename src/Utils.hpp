#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
// Importa la mesh poligonale e verifica se è corretta
// mesh: una struct PolygonalMesh
// restituisce il risultato della lettura, true se la lettura ha esito positivo, falso altrimenti
bool ImportMesh(PolygonalMesh& mesh);

// Importa le proprietà di Cell0D dal file Cell0Ds.csv
// mesh: una struct PolygonalMesh
// restituisce il risultato della lettura, true se la lettura ha esito positivo, falso altrimenti
bool ImportCell0Ds(PolygonalMesh& mesh);

// Importa le proprietà di Cell1D dal file Cell1Ds.csv
// mesh: una struct PolygonalMesh
// restituisce il risultato della lettura, true se la lettura ha esito positivo, falso altrimenti
bool ImportCell1Ds(PolygonalMesh& mesh);

// Importa le proprietà di Cell2D dal file Cell2Ds.csv
// mesh: una struct PolygonalMesh
// restituisce il risultato della lettura, true se la lettura ha esito positivo, falso altrimenti
bool ImportCell2Ds(PolygonalMesh& mesh);

}
