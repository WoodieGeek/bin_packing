#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H
#include "bin_packing.h"
#include <QDebug>

class TGenetic {
public:
    TAnswer Solve(const TBinPacking &problem) {
        const auto& weights = problem.GetWeights();
        c = problem.GetC();
        size_t n = problem.GetWeights().size();
        std::vector<int> baseParent1 = weights;
        add(baseParent1);
        std::vector<int> baseParent2;

        for (size_t i = n; i>0; i--) {
            baseParent2.push_back(weights[i-1]);
            weightsCount[weights[i-1]]++;
        }
        add(baseParent2);

        while(iterationNum >0){
            getParent();
            crossing();
            populationCheck();
            iterationNum--;
        }

        //if(bestAnswer == 1) return Population[Population.size()-1];

        getAnswer();

        return best;

    }

private:
    void chekAnswer(std::vector<int> ans){
        std::map<int,int> tmpMap;
        for(size_t i=0; i<ans.size();i++){
            tmpMap[ans[i]]++;
        }
        for (auto item: weightsCount){
            int tmp1 = weightsCount[item.first];
            int tmp2 = tmpMap[item.first];
            int count = tmp1-tmp2;
            if(count < 0){
                while (count != 0) {
                    for (size_t i=0; i<ans.size();i++) {
                        if(ans[i]==item.first && count != 0){
                            ans.erase(ans.begin()+i);
                            count++;
                        }
                    }
                }
            }
            if(count > 0){
                while (count != 0) {
                    ans.push_back(item.first);
                    count--;
                }
            }
        }

        mutation(ans);
    }

    void mutation (std::vector<int> ans){
        for (size_t i=0;i<Population.size();i++) {
            auto pop = decode(Population[i]);
            size_t cnt=0;
            for (size_t j=0;j<ans.size();j++) {
                if(ans[j]==pop[j]) cnt++;
            }
            if(cnt == ans.size()){
                size_t num = 10;
                while (num != 0) {
                    size_t rndIndx1 = qrand() % ans.size();
                    size_t rndIndx2 = qrand() % ans.size();
                    std::swap(ans[rndIndx1],ans[rndIndx2]);
                    num--;
                }
            }
        }
        add(ans);
    }

    std::vector<int> decode(TAnswer plane){
        std::vector<int> decode_;
        for (size_t i=0;i<plane.Plane.size();i++) {
            for (size_t j=0; j<plane.Plane[i].size();j++) {
                decode_.push_back(plane.Plane[i][j]);
            }
        }
        return decode_;
    }

    void crossing(){
        std::vector<int> Parent1 = decode(this->Parents[0]);
        std::vector<int> Parent2 = decode(this->Parents[1]);

        std::vector<int> child1 = Parent1;
        std::vector<int> child2 = Parent2;
        size_t n = Parent1.size();
        size_t sep = n/3;
        for (size_t i=0, j=n-1; i<sep, j>sep*2; i++, j--) {
            auto tmp = child1[i];
            child1[i] = Parent2[i];
            Parent2[i] = tmp;

            tmp = child1[j];
            child1[j] = Parent2[j];
            Parent2[j] = tmp;

            tmp = Parent1[i];
            Parent1[i] = Parent2[i];
            Parent2[i] = tmp;

            tmp = Parent1[j];
            Parent1[j] = child2[j];
            child2[j] = tmp;
        }

        chekAnswer(child1);
        chekAnswer(child2);
    }

    void add(std::vector<int> ans){
        size_t sum=0, surpluses=0;
        TAnswer answer;
        std::vector<int> line;
        for (size_t i=0; i<ans.size(); i++) {
            if(sum+ans[i] > c) {
                surpluses+=c-sum;
                answer.Plane.push_back(line);
                line.resize(0);
                line.push_back(ans[i]);
                if(i==ans.size()-1){
                    answer.Plane.push_back(line);
                }
                sum=ans[i];
            }
            else {
                line.push_back(ans[i]);
                sum+=ans[i];
                if(i==ans.size()-1){
                    answer.Plane.push_back(line);
                }
            }
        }
//        if (surpluses == 0){
//            bestAnswer = 1;
//            Population.push_back(answer);
//        }
        Population.push_back(answer);
    }

    void getParent(){
        if(Population.size()==2){
            Parents.push_back(Population[0]);
            Parents.push_back(Population[1]);
        }
        else {
            Parents.resize(0);
            size_t indx1,indx2;
            size_t min = 999999;
            for (size_t i=0;i<Population.size();i++) {
                if(min > Population[i].Plane.size()) {
                    min = Population[i].Plane.size();
                    indx1 = i;
                }
            }
            Parents.push_back(Population[indx1]);
            min = 999999;
            for (size_t i=0;i<Population.size();i++) {
                if(min > Population[i].Plane.size() && i != indx1) {
                    min = Population[i].Plane.size();
                    indx2 = i;
                }
            }
            Parents.push_back(Population[indx2]);
        }
    }

    void getAnswer(){
        size_t indx;
        size_t min = 999999;
        for (size_t i=0;i<Population.size();i++) {
            if(min > Population[i].Plane.size()) {
                min = Population[i].Plane.size();
                indx = i;
            }
        }
        auto tmp = decode(Population[indx]);

        size_t sum=0, surpluses=0;
        std::vector<int> line;
        for (size_t i=0; i<tmp.size(); i++) {
            if(sum+tmp[i] > c) {
                surpluses+=c-sum;
                best.Plane.push_back(line);
                line.resize(0);
                line.push_back(tmp[i]);
                if(i==tmp.size()-1){
                    best.Plane.push_back(line);
                }
                sum=tmp[i];
            }
            else {
                line.push_back(tmp[i]);
                sum+=tmp[i];
                if(i==tmp.size()-1){
                    best.Plane.push_back(line);
                }
            }
        }
        best.Length = c;

    }

    void populationCheck(){
        if(Population.size() > 50){
            Parents.resize(0);
            size_t indx1,indx2;
            size_t max = 0;
            for (size_t i=0;i<Population.size();i++) {
                if(max < Population[i].Plane.size()) {
                    max = Population[i].Plane.size();
                    indx1 = i;
                }
            }
            max = 0;
            for (size_t i=0;i<Population.size();i++) {
                if(max < Population[i].Plane.size() && i != indx1) {
                    max = Population[i].Plane.size();
                    indx2 = i;
                }
            }
            std::vector<TAnswer> tmp;
            for (size_t i=0;i<Population.size();i++) {
                if(i==indx1) continue;
                if(i==indx2) continue;
                tmp.push_back(Population[i]);
            }
            Population.resize(0);
            for (size_t i=0;i<tmp.size();i++) {
                Population.push_back(tmp[i]);
            }
//            Population.erase(Population.begin()+indx1);
//            Population.erase(Population.begin()+indx2);

        }
    }

private:
    std::vector<TAnswer> Population;
    std::vector<TAnswer> Parents;
    std::map <int,int> weightsCount;
    bool bestAnswer =0;
    TAnswer best;
    size_t iterationNum = 100;
    int c = 0;

};

#endif // GENETIC_ALGORITHM_H
