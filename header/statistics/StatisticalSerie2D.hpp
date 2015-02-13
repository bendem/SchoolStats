#ifndef STATSTICALSERIE2D_HPP
#define STATSTICALSERIE2D_HPP

class StatisticalSerie2D {
private:
    Sample* sample;
    const DataSource& dataSource;
    float averageValue1;
    float averageValue2;
    float coefficientA;
    float coefficientB;
public:
    StatisticalSerie2D(Sample*);

    void display();
    void forecast();
    int menu();
    void computeAverages();
    void computeCoefficient();

    float getCoefficientA() const;
    void setCoefficientA(float coefficientA);
    float getCoefficientB() const;
    void setCoefficientB(float coefficientB);
    float getAverageValue1() const;
    void setAverageValue1(float averageValue1);
    float getAverageValue2() const;
    void setAverageValue2(float averageValue2);
};

#endif
