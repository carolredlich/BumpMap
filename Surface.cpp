/* 
 * File:   Surface.cpp
 * Author: caroline
 * 
 * Created on 25 de Abril de 2016, 12:18
 */

#include "Surface.h"


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Surface::Surface( SphereShader *shader )
{
    _shader = shader;

    const int n = 100;
    const int m = 100;

    const int numTriangles = 2 * n * m;
    const int numVertices = ( n + 1 ) * ( m + 1 );

    _triangles.resize( 3 * numTriangles );

    _vertex.resize( 3 * numVertices );
    _normal.resize( 3 * numVertices );
    _tangent.resize( 3 * numVertices );
    _bitangent.resize( 3 * numVertices );

    _texCoord.resize( 2 * numVertices );

    for( unsigned int i = 0; i <= n; i++ )
    {
        for( unsigned int j = 0; j <= m; j++ )
        {
            //Calcula o indice no vetor
            unsigned int k = getVectorIndex( i, j, n );

            //Salva as coordenadas de textura
            _texCoord[ 2 * k + 0 ] = ( double ) i / n;
            _texCoord[ 2 * k + 1 ] = ( double ) j / m;

            //Calcula os parâmetros
            double theta = 2 * _texCoord[2 * k + 0] * M_PI;
            double phi = _texCoord[2 * k + 1] * M_PI;
            double sinTheta = sin( theta );
            double cosTheta = cos( theta );
            double sinPhi = sin( phi );
            double cosPhi = cos( phi );

            //Calcula os vértices == equacao da esfera
            _vertex[3 * k + 0 ] = cosTheta * sinPhi;
            _vertex[3 * k + 1 ] = cosPhi;
            _vertex[3 * k + 2 ] = sinTheta * sinPhi;

            //Normal == vertices
            _normal[3 * k + 0 ] = _vertex[3 * k + 0 ];
            _normal[3 * k + 1 ] = _vertex[3 * k + 1 ];
            _normal[3 * k + 2 ] = _vertex[3 * k + 2 ];

//            //Calcula o vertor tangente == dS/DTheta
//            _tangent[3 * k + 0 ] = -sinTheta * sinPhi;
//            _tangent[3 * k + 1 ] = 0.0;
//            _tangent[3 * k + 2 ] = cosTheta * sinPhi;
//
//            //Calcula o vertor bitangente  == dS / dPhi
//            _bitangent[3 * k + 0 ] = cosTheta * cosPhi;
//            _bitangent[3 * k + 1 ] = -sinPhi;
//            _bitangent[3 * k + 2 ] = sinTheta * cosPhi;
            
            //Calcula o vertor tangente == dS/DTheta
            _tangent[3 * k + 0 ] = 0.0;
            _tangent[3 * k + 1 ] = 0.0;
            _tangent[3 * k + 2 ] = 0.0;

            //Calcula o vertor bitangente  == dS / dPhi
            _bitangent[3 * k + 0 ] = 0.0;
            _bitangent[3 * k + 1 ] = 0.0;
            _bitangent[3 * k + 2 ] = 0.0;

        }
    }

    //Preenche o vetor com a triangulação
    unsigned int k = 0;
    for( unsigned int i = 0; i < n; i++ )
    {
        for( unsigned int j = 0; j < m; j++ )
        {
            _triangles[k++ ] = getVectorIndex( i, j, n );
            _triangles[k++ ] = getVectorIndex( i + 1, j + 1, n );
            _triangles[k++ ] = getVectorIndex( i + 1, j, n );
            _triangles[k++ ] = getVectorIndex( i, j, n );
            _triangles[k++ ] = getVectorIndex( i, j + 1, n );
            _triangles[k++ ] = getVectorIndex( i + 1, j + 1, n );
        }
    }


}

Surface::~Surface( ) { }



