#ifndef BOID_H
#define BOID_H

#define Xmin -50.0
#define Xmax 50.0
#define Ymin -50.0
#define Ymax 50.0
#define Zmin -50.0
#define Zmax 50.0

#define vel_MAX 1.00
#define vel_MIN -1.00
#define pb push_back
#define freq_pankh 3

float random_float(int mi,int mx);

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

        //! bool operator + for vertex_2d
        tuple operator + (const tuple& rhs);

        //! bool operator + for vertex_2d
        tuple operator * (const float& rhs);

        //! function to shift a tuple wrt to a reference tuple
        /*!
          \param ref_tuple reference tuple chosen as origin
        */
        void shift_it(tuple ref_tuple);

        //! function to return the distance b/w to points
        float distance(tuple a);

        //! function to return the magnitude of the tuple
        float magnitude();

        //! function to make it unit vector
        void make_it_unit_vector();
};

tuple cross_product(tuple a, tuple b);
float dot_product(tuple a, tuple b);

/*! \class boid
    \brief class for a boid
*/
class boid{
    public:
        tuple position; //!< position of the boid
        tuple velocity; //!< velocity of the boid

        //! Constructor
        boid(tuple position, tuple velocity);

        //! Constructor
        boid(tuple position);

        //! Constructor
        boid();        

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
