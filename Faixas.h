//
//  Faixas.h
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 28/04/21.
//  Copyright © 2021 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Faixas_h
#define Faixas_h

class Faixa{
    vector<int> ArestasNaFaixa;
public:
    void CadastraAresta(int a)
    {
        ArestasNaFaixa.push_back(a);
    }
};

class ConjuntoDeFaixas{
    vector<Faixa> TodasAsFaixas;
public:
    void CadastraArestaNaFaixa(int f, int a)
    {
        TodasAsFaixas[f].CadastraAresta(a);
    }
    void CriaFaixas(int qtdDeFaixas) // pode ser substituída por uma construtora
    {
        for (int i=0; i<qtdDeFaixas; i++)
            TodasAsFaixas.push_back(Faixa());
    }
};


#endif /* Faixas_h */
