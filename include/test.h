class Forme {
protected:
    double x, y;  // attributs communs à toutes les formes

public:
    Forme(double x, double y) : x(x), y(y) {}

    virtual double aire() const = 0; // fonction virtuelle pure
    virtual ~Forme() = default;
};

class Cercle : public Forme {
public:
    Cercle(double x, double y, double r) 
        : Forme(x, y), rayon(r) {}

    double aire() const override {
        return 3.14 * rayon * rayon;
    }

private:
    double rayon;
};
