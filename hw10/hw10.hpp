// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12
#ifndef HW10_HPP
#define HW10_HPP
#include <vector>
class polynomial
{
private:
    std::vector<double> coefficients;
public:
    polynomial(const std::vector<double> coefficients)
    {
        if (coefficients.empty() || coefficients[0] == 0.0)
        {
            throw std::invalid_argument("The zero-th coefficient must be non-zero");
        }
        this->coefficients = coefficients;
    };
    bool is_odd() const { return coefficients.size() % 2 == 0; };
    double evaluate_at(double x) const
    {
        double result = coefficients[0]; // Initialize with the highest-degree coefficient
        for (int i = 1; i < coefficients.size(); i++)
        {
            result = result * x + coefficients[i]; // Horner's method
        }
        return result;
    };
    double operator()(double x) const { return evaluate_at(x); };
};
void find_initial_bounds(const polynomial &p, double &left, double &right)
{
    if (!p.is_odd() || left >= right)
    {
        throw std::invalid_argument("Invalid initial bounds");
    }
    while(p(left)*p(right)>0){
        left--;
        right++;
    }
    double leftval = p(left);
    double rightval = p(right);
}
void move_bounds_closer(const polynomial &p, double &left, double &right, bool trace = false)
{
    find_initial_bounds(p, left, right);
    // Calculate the midpoint between the current bounds
    double midpoint = (left + right) / 2;
    // Evaluate the polynomial at the midpoint
    double midpoint_val = p(midpoint);
    // Adjust the bounds based on the sign of the midpoint value
    if (midpoint_val * p(left) < 0)
    {
        right = midpoint;
    }
    else
    {
        left = midpoint;
    }
};
double find_zero(const polynomial &p, long prec, bool trace = false)
{
    double left = 10; // Initial bounds
    double right = 11;
    find_initial_bounds(p, left, right);
    if (!p.is_odd() || left >= right)
    {
        throw std::invalid_argument("Invalid initial bounds");
    }
    double leftval = p(left);
    double rightval = p(right);
    if (leftval * rightval > 0)
    {
        throw std::invalid_argument("Initial bounds do not contain a root");
    }
    double midpoint = (left + right) / 2;
    while (right-left > prec || right!=left)
    {
        cout << "midpoint " << p(midpoint) << std::endl;
        cout << "left " << left << std::endl;
        cout << "right " << right << std::endl;
        cout << "left val " << leftval << std::endl;
        cout << "right val " << rightval << std::endl;
        if(midpoint == 4.36557e-11)
            break;
        midpoint = (left + right) / 2;
        rightval = p(right);
        leftval = p(left);
        move_bounds_closer(p,left,right);
        // midpoint = (left + right) / 2;
        // double midpoint_val = p(midpoint);
        // if (midpoint_val * leftval < 0)
        // {
        //     right = midpoint;
        // }
        // else
        // {
        //     left = midpoint;
        // }
    }
    return (left + right) / 2;
}
double evaluate_at(const polynomial &p, double x)
{
    return p(x);
}
#endif