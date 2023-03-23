#include "Quadtree.h"

Quadtree::Quadtree()
{
}

Quadtree::Quadtree(float xX, float xY, float nX, float nY, vector<Ponto> &p, int n, Quadtree* address)
{
    children = (Quadtree*)calloc(4, sizeof(Quadtree));
    childrenSize = 0;
    pointsSize = 0;
    nPoints = n;
    points = (int*)calloc(p.size(), sizeof(int));
    pontosCenario = p;
    this->address = address;
    this->maxX = xX;
    this->maxY = xY;
    this->minX = nX;
    this->minY = nY;
    this->meioX = (xX + nX)/2;
    this->meioY = (xY + nY)/2;
    this->meiaLarguraX = (xX - nX)/2;
    this->meiaLarguraY = (xY - nY)/2;
    countPoints();
}

Quadtree::Quadtree(float xX, float xY, float nX, float nY, int* ps, int pointsSize, Quadtree* address, Quadtree* Parent)
{
    children = (Quadtree*)calloc(4, sizeof(Quadtree));
    childrenSize = 0;
    this->pointsSize = 0;
    this->address = address;
    this->Parent = Parent;
    //cout << "error debugged?!\n";
    points = (int*)calloc(pointsSize, sizeof(int));
    //cout << "yes!\n";
    this->maxX = xX;
    this->maxY = xY;
    this->minX = nX;
    this->minY = nY;
    this->meioX = (xX + nX)/2;
    this->meioY = (xY + nY)/2;
    this->meiaLarguraX = (xX - nX)/2;
    this->meiaLarguraY = (xY - nY)/2;
    countPoints(ps, pointsSize);
}

void Quadtree::countPoints()
{
    pointsSize = pontosCenario.size();
    if(nPoints >= pointsSize) return;

    for(int i = 0; i < pointsSize; i++)
    {
        *(points + i) = i;
    }
    childrenSize = 4;
    genChildren();
    cumulativePoints = pointsSize;
    pointsSize = 0;
    free(points);
}

void Quadtree::countPoints(int *ps, int pSize)
{
    for(int i = 0; i < pSize; i++)
    {
        int ptr = *(ps + i);
        Ponto ponto = pontosCenario[ptr];
        if(ponto.x >= minX && ponto.x <= maxX && ponto.y >= minY && ponto.y <= maxY)
        {
            *(this->points + this->pointsSize) = ptr;
            this->pointsSize++;
        }
    }

    cumulativePoints = pointsSize;
    if(pointsSize > nPoints)
    {
        //cout << "Splitting node\tpointSize " << pointsSize << " > nPoints " << nPoints << endl;
        childrenSize = 4;
        genChildren();;
        pointsSize = 0;
        free(points);
    } else{
        leafNodes.push_back(address);
        //cout << this <<" " << this->pointsSize << endl;
    }
}

void Quadtree::genChildren()
{
    //cout <<"gen children\n";
    Quadtree q1 = Quadtree(meioX, maxY, minX, meioY, points, pointsSize, &children[0], address);
    Quadtree q2 = Quadtree(maxX, maxY, meioX, meioY, points, pointsSize, &children[1], address);
    Quadtree q3 = Quadtree(meioX, meioY, minX, minY, points, pointsSize, &children[2], address);
    Quadtree q4 = Quadtree(maxX, meioY, meioX, minY, points, pointsSize, &children[3], address);
    children[0] = q1;
    children[1] = q2;
    children[2] = q3;
    children[3] = q4;
}

void Quadtree::draw()
{
    if(childrenSize == 0) return;
    glLineWidth(1);
    glColor3f(1,1,1); // R, G, B  [0..1]
    glBegin(GL_LINES);
        glVertex2f(meioX, maxY);
        glVertex2f(meioX, minY);
        glVertex2f(maxX, meioY);
        glVertex2f(minX, meioY);
    glEnd();
    for (int i = 0; i < childrenSize; i++)
    {
        children[i].draw();
    }
}

void Quadtree::resetPoints(int n)
{
    int temp = nPoints;
    nPoints = n;

    if(n > temp)
    {
        leafNodes.clear();
        treeDFS();
    }
    else if(n < temp)
    {
        vector<Quadtree*> tempVector;
        tempVector = leafNodes;
        leafNodes.clear();
        for (int i = 0; i < tempVector.size(); i++)
        {
            tempVector[i]->countPoints(points, 0);
        }
    }
}

int* Quadtree::treeDFS(Quadtree* node, int* ptr)
{
    if(cumulativePoints <= nPoints && ptr == NULL)
    {
        points = (int*)calloc(nPoints, sizeof(int));
        ptr = points;
        node = address;
        leafNodes.push_back(address);
        //cout << pointsSize << endl;
        for (int i = 0; i < childrenSize; i++)
        {
            children[i].treeDFS(node, ptr);
        }
        //cout << pointsSize << " endl " << (ptr - points)/4 << endl;
        free(children);
        childrenSize = 0;
        //points = (int*)realloc(points, pointsSize*4);
        return 0;
    }
    if(node != NULL && node->pointsSize == node->cumulativePoints) return 0;
    for (int i = 0; i < childrenSize; i++)
    {
        //cout << i << "calling children\n";
        ptr = children[i].treeDFS(node, ptr);
    }
    if(ptr == NULL) return 0;
    for (int i = 0; i < pointsSize; i++)
    {
        *ptr = points[i];
        ptr++;
    }
    node->pointsSize += pointsSize;
    free(children);
    return ptr;

}

void Quadtree::print()
{
    for (int i = 0; i < childrenSize; i++)
    {
        //cout << &children[i] << endl;
        if(childrenSize > 0) children[i].print();
    }
}
