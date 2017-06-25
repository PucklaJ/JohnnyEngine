#include <mathematics.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <Actor.h>
#include <MainClass.h>

namespace SDL
{
    double abs(const double& d)
    {
        if(d < 0.0)return -d;
        else return d;
    }
    
    int getRand(int min,int max)
    {
        return rand() % (max - min+1) + (min);
    }
    
    bool luck(int percent)
    {
        return getRand(1,100) <= percent;
    }
    
    inline int calculateF(const A_Square& pos, const A_Square& target,int previousCosts)
    {
        return (int)(abs(target.x - pos.x) + abs(target.y - pos.y) + pos.g + previousCosts); 
    }
    
    inline bool squareEquals(const A_Square& s1, const A_Square& s2)
    {
        return s1.x == s2.x && s1.y == s2.y;
    }
    
    inline int getBestSquareIndex(const std::vector<A_Square*>& openList,const A_Square& target,int& previousCosts)
    {
        int minf = calculateF(*openList[0],target,previousCosts);
        int minI = 0;
        for(size_t i = 1;i<openList.size();i++)
        {
            int f = calculateF(*openList[i],target,previousCosts);
            if(f < minf)
            {
                minf = f;
                minI = (int)i;
            }
        }
        
        previousCosts+=minf;
        
        return minI;
    }
    
    // up right down left
    inline void getNeighbourIndices(const A_Square& pos, const std::vector<A_Square>& squares,int w,int indices[])
    {
        indices[0] = -1;
        indices[1] = -1;
        indices[2] = -1;
        indices[3] = -1;
        
        // up
        if(pos.y != 0)
        {
            indices[0] = (pos.y-1) * w + pos.x;
        }
        
        //right
        if(pos.x < (w-1))
        {
            indices[1] = pos.y * w + pos.x+1;
        }
        
        //down
        if(pos.y < ((int)squares.size()/w-1))
        {
            indices[2] = (pos.y+1) * w + pos.x;
        }
        
        // left
        
        if(pos.x != 0)
        {
            indices[3] = pos.y * w + pos.x-1;
        }
    }
    
    inline bool Contains(const std::vector<A_Square*>& List,const A_Square& s)
    {
        for(size_t i = 0;i<List.size();i++)
        {
            if(squareEquals(*List[i],s))
                return true;
        }
        
        return false;
    }
    
    inline void removeFromOpen(std::vector<A_Square*>& openList,const A_Square& s)
    {
        for(size_t i = 0;i<openList.size();i++)
        {
            if(squareEquals(*openList[i],s))
            {
                openList[i] = openList.back();
                openList.pop_back();
                return;
            }
        }
    }
    
    std::vector<A_Square> a_stern(std::vector<A_Square>& field,A_Square& start,A_Square& target,int w)
    {
        std::vector<A_Square*> openList;
        std::vector<A_Square*> closedList;
        std::vector<A_Square> path;
        A_Square* current = nullptr;
        A_Square* neighbourSquare = nullptr;
        int neighbours[4];
        int costs = 0;
        
        openList.push_back(&start);
        
        do
        {
            current = openList[getBestSquareIndex(openList,target,costs)];
            
            if(!squareEquals(*current,target))
            {
                getNeighbourIndices(*current,field,w,neighbours);
            
                for(int i = 0;i<4;i++)
                {
                    if(neighbours[i] == -1)
                        continue;
                        
                    neighbourSquare = &field[neighbours[i]];
                    
                    if(!neighbourSquare->solid && !Contains(closedList,*neighbourSquare) && !Contains(openList,*neighbourSquare))
                    {
                        openList.push_back(neighbourSquare);
                        neighbourSquare->m_previous = current;
                    }
                }
                
                removeFromOpen(openList,*current);
                closedList.push_back(current);
                
                if(openList.empty())
                {
                    return path;
                }
            }
            else
            {
                closedList.push_back(current);
                break;
            }
        }while(true);
        
        A_Square* prev = current->m_previous;
        
        while(prev)
        {
            path.push_back(*prev);
            prev = prev->m_previous;
        }
        
        reverse(path);
        
        return path;
    }
}
