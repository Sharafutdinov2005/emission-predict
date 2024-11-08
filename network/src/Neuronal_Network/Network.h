#ifndef NETWORK_DEFENCE
#define NETWORK_DEFENCE 1

#include "eigen-3.4.0/Eigen/Eigen"

namespace NeuralNetwork
{
    typedef size_t              Number;
    typedef double              Scalar;
    typedef Eigen::MatrixXf     Matrix;
    typedef Eigen::RowVectorXf  RowVector;
    typedef Eigen::VectorXf     ColumnVector;


    class NeuralNetwork {
    public:
	    NeuralNetwork(
            std::vector<Number> s,
            Scalar l = Scalar(0.005)
        );

        NeuralNetwork(
            std::vector<Number> s,
            std::vector<Matrix*> w
        );

        std::vector<Scalar> predict(
            std::vector<Scalar>& input
        );

        Scalar get_error(
            std::vector<RowVector*> data
        );

        NeuralNetwork(
            const NeuralNetwork&
        ) = delete;

        NeuralNetwork& operator= (
            const NeuralNetwork&
        ) = delete;

    private:
	    void train(
            std::vector<RowVector*> data
        );

	    void propagate_forward(
            RowVector& input
        );

	    void propagate_backward(
            RowVector& output
        );

	    void calculate_errors(
            RowVector& output
        );

	    void update_weights();

        void initialize_storage_objects();

        // initializes layer of weigths with random values
        // initializes bias neurons
        void initialize_storage_objects_layer(
            Number layer
        );

        std::vector<Number> validate_structure(
            std::vector<Number> s
        ) const;

        Scalar validate_learning_rate(
            Scalar l
        ) const;

        std::vector<Matrix*> validate_weights(
            std::vector<Matrix*> w
        ) const;

	    // storage objects for working of neural network
	    /*
		use pointers when using std::vector<Class> as std::vector<Class> calls destructor of 
		Class as soon as it is pushed back! when we use pointers it can't do that, besides
		it also makes our neural network class less heavy!! It would be nice if you can use
		smart pointers instead of usual ones like this
		*/

        std::vector<Number>     structure;
	    std::vector<RowVector*> neuron_layers;  // stores the different layers of out network
	    std::vector<RowVector*> cache_layers;   // stores the unactivated (activation fn not yet applied) values of layers
	    std::vector<RowVector*> deltas;         // stores the error contribution of each neurons
	    std::vector<Matrix*>    weights;        // the connection weights itself
	    Scalar learning_rate;
    };
}

#endif