
class Piece{
public:
    Piece(const int &x, const int &y):_x(x), _y(y), _z(0){};
    int get_x() const;
    int get_y() const;
    int get_z() const;
    virtual void move(const int &x, const int &y);
protected:
    int _x;
    int _y;
    int _z;
    bool can_move = false;
};


class Bee : public Piece {

};

class Ant : public Piece {

};

class Beetle : public Piece {
    void move(const int &x, const int &y, const int &z);
};

class Grasshopper : public Piece {

};

class Spider : public Piece {

};
