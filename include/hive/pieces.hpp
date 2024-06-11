#ifndef PIECES_HPP
#define PIECES_HPP
#pragma once


#include <vector>
#include <hive/coordinates.hpp>
#include <hive/namespaces.hpp>


namespace hive {
    class Insect{
    public:
        Insect() noexcept {this->_exist = false;};
        explicit Insect(const Coords &c) noexcept:_c(c) {this->color = DEFAULT;};
        Insect(const Coords &c, const Color &color) noexcept:_c(c), color(color) {};
        Insect(const Coords &c, const Color &color, const InsectType &type) noexcept;
        virtual ~Insect() noexcept {};
        virtual const Coords &get_location() const noexcept;
        virtual const int &get_color() const noexcept;
        virtual void move(const Coords &c) noexcept;
        virtual const InsectType &get_type() const noexcept;
        virtual std::vector<Coords> get_surrounding_locations() const noexcept;
        virtual void set_move(const bool &m) noexcept;
        virtual const bool &can_move() const noexcept;
        virtual const bool &is_exist() const noexcept;
        virtual const bool &can_jump() const noexcept;
        virtual bool operator==(const Insect &p) const noexcept;
    protected:
        Coords _c;
        Color color = DEFAULT;
        bool _move = false;
        bool _exist = true;
        bool _jump = false;
        InsectType type = InsectType::NONTYPE;
    };


    class Bee : public Insect {
    public:
        Bee(const Coords &c, const Color &color) noexcept;
        virtual ~Bee() noexcept {};
    };

    class Ant : public Insect {
    public:
        Ant(const Coords &c, const Color &color) noexcept;
        virtual ~Ant() noexcept {};
    };

    class Beetle : public Insect {
    public:
        Beetle(const Coords &c, const Color &color) noexcept;
        virtual ~Beetle() noexcept {};
    };

    class Grasshopper : public Insect {
    public:
        Grasshopper(const Coords &c, const Color &color) noexcept;
        virtual ~Grasshopper() noexcept {};
    };

    class Spider : public Insect {
    public:
        Spider(const Coords &c, const Color &color) noexcept;
        virtual ~Spider() noexcept {};
    };

    #ifdef LADYBUG_E
    class LadyBug : public Insect {
        LadyBug(const Coords &c, const Color &color) noexcept;
        virtual ~LadyBug() noexcept {};
    };
    #endif

    #ifdef MOSQUITO_E
    class Mosquito : public Insect {
        Mosquito(const Coords &c, const Color &color) noexcept;
        virtual ~Mosquito() noexcept {};
    };
    #endif

    #ifdef PILLBUG_E
    class PillBug : public Insect {
        PillBug(const Coords &c, const Color &color) noexcept;
        virtual ~PillBug() noexcept {};
    };
    #endif
}


#endif
