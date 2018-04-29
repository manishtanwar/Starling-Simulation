#ifndef BOID_H
#define BOID_H

/*! \class tuple
    \brief class for a tuple
*/
class tuple{
    public:
        float x; //!< x-coordinate of the tuple
        float y; //!< y-coordinate of the tuple
        float z; //!< z-coordinate of the tuple

        //! Constructor
        tuple(float x, float y, float z);

        //! Constructor
        tuple();

        //! bool operator == for vertex_2d
        bool operator == (const tuple& rhs);

        //! bool operator < for vertex_2d
        bool operator < (const tuple& rhs);

        //! function to shift a tuple wrt to a reference tuple
        /*!
          \param ref_tuple reference tuple chosen as origin
        */
        void shift_it(tuple ref_tuple);
};

/*! \class boid
    \brief class for a boid
*/
class boid{
    public:
        tuple position; //!< position of the boid
        tuple velocity; //!< velocity of the boid
        tuple force; //!< force(attraction and repulsion due to neighbours) on the boid

        //! Constructor
        boid(tuple position, tuple velocity);

        //! Constructor
        boid(tuple position);

        // //! bool operator == for vertex_2d
        // bool operator == (const vertex_2d& rhs);

        // //! bool operator < for vertex_2d
        // bool operator < (const vertex_2d& rhs);

        // //! function to shift a vertex wrt to a reference vertex
        // /*!
        //   \param ref_vertex reference vertex chosen as origin
        // */
        // void shift_it(vertex_2d ref_vertex);
};


#endif