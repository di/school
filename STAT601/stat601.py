from __future__ import division
import math
import numpy as np
from scipy import stats
import ols
import itertools
from studentized_range import q_a

# Chapter Five

def binomial_probability(n, pi, X):
    print "P(X=%d) = %f" % (X, bp(n, pi, X))
    print "P(X<%d) = %f" % (X, sum([bp(n, pi, x) for x in range(0, X)]))
    print "P(X<=%d) = %f" % (X, sum([bp(n, pi, x) for x in range(0, X+1)]))
    print "P(X>%d) = %f" % (X, sum([bp(n, pi, x) for x in range(X+1, n+1)]))
    print "P(X>=%d) = %f" % (X, sum([bp(n, pi, x) for x in range(X, n+1)]))

def bp(n, pi, X):
    q = (1.0 - pi) # probability of failure

    n_min_X = n - X
    n_fact = math.factorial(n)
    X_fact = math.factorial(X)

    return ( n_fact / ( math.factorial(n_min_X) * X_fact ) ) * (math.pow(pi,X)) * (math.pow(q,n_min_X))

# Chapter Six

def standardized_normal_dist(Z):
    print "P(Z<%f) = %f" % (Z, stats.norm.cdf(Z))
    print "P(Z>%f) = %f" % (Z, 1-stats.norm.cdf(Z))

def find_x_value(mu, Z, sigma):
    return mu + Z * sigma

def find_z_value(X, mu, sigma):
    return (X - mu) / sigma

# Chapter Seven

def find_z_value2(x_bar, mu, sigma, n):
    return z_test_for_the_mean(x_bar, mu, sigma, n)

def find_z_value3(n, p, pi):
    # p = probability of occurrence
    # pi = actual probability
    return ((p-pi) / math.sqrt((pi*(1-pi))/n))

def find_z_value_from_percentage(p):
    # p = percentage (inverse cdf)
    return stats.norm.ppf(p)

def find_percentage_from_z(Z, pi):
    # find the percentage given a z value and a known percentage
    return ((Z*math.sqrt((pi*(1-pi))/100))+pi)*100

# Chapter Eight

def z_confidence_interval(x_bar, sigma, n, p):
    # p is percentage as a decimal
    alpha = (1-p)
    z_low = round(find_z_value_from_percentage(alpha/2), 2)
    z_high = round(find_z_value_from_percentage(p + alpha/2), 2)
    low = x_bar + z_low * (sigma / math.sqrt(n)) 
    high = x_bar + z_high * (sigma / math.sqrt(n)) 
    print "%f <= mu <= %f" % (low, high)

def upper_tail_critical_t_value(alpha, n):
    return stats.t.isf(alpha/2, n-1)

def t_confidence_interval(x_bar, S, n, p):
    # p is percentage as a decimal
    # sigma is unknown!
    alpha = (1-p)
    z_high = round(upper_tail_critical_t_value(alpha, n), 2)
    z_low = -z_high
    low = x_bar + z_low * (S / math.sqrt(n)) 
    high = x_bar + z_high * (S / math.sqrt(n)) 
    print "%f <= mu <= %f" % (low, high)

# Chapter Nine

def reject_null_hypothesis(critical_value, t_stat):
    if -abs(critical_value) < t_stat < abs(critical_value):
        return False
    return True

def reject_null_hypothesis2(p_value, alpha):
    # Alpha is the level of significance
    if p_value < alpha:
        return True
    else:
        return False

def one_tail_p_value(t_stat, n):
    return stats.t.sf(np.abs(t_stat), n-1)

def two_tail_p_value(t_stat, n):
    return one_tail_p_value(t_stat, n)*2

def z_test_for_the_mean(x_bar, mu, sigma, n):
    # x_bar = sample mean
    # mu = actual mean
    # sigma = actual standard dev
    # Sigma is known
    return ((x_bar - mu) / (sigma / math.sqrt(n)))

def z_test_for_the_mean2(x_bar, mu, S, n):
    # Sigma is unknown
    return ((x_bar - mu) / (S / math.sqrt(n)))

def z_test_for_the_proportion(X, n, pi):
    # In terms of the number of events of interest, X
    # pi = the proportion
    return ((X - n*pi) / math.sqrt(n*pi*(1-pi)))

def sample_proportion(X, n):
    # X = number of events of interest
    # n = sample size
    # p = sample proportion
    return X/n

# Chapter 10

# Pooled-Variance t Test for the Difference Between Two Means
def pvttest(X_1, S1, n1, X_2, S2, n2, u1=0, u2=0):
    # Where:
    # X_ = the mean of the sample of the individual population
    # S = the variance of the sample of the individual population
    # n = the size of the samle of the individual population
    # u = population means
    Sp = pooled_variance(S1, n1, S2, n2)
    t_stat = ((X_1-X_2)-(u1-u2))/math.sqrt(Sp*(1/n1 + 1/n2))
    return t_stat

def pooled_variance(S1, n1, S2, n2):
    # S = the variance of the sample of the individual population
    # n = the size of the samle of the individual population
    return ((n1-1)*S1**2 + (n2-1)*S2**2)/(n1-1 + n2-1)

def find_critical_value(alpha, n1, n2, tails=1):
    degrees_of_freedom = n1 + n2 - 2
    return stats.t.isf(alpha, degrees_of_freedom)*tails

def find_p_value(t_stat, n1, n2, tails=1):
    degrees_of_freedom = n1 + n2 - 2
    return stats.t.sf(np.abs(t_stat), degrees_of_freedom)*tails

# Chapter 11

# Reject H0 if p-value < alpha

def grand_mean(vals):
    # Finds the grand mean of multiple groups
    s = 0
    n = 0
    for g in vals:
        s += sum(g)
        n += len(g)
    return s/n

def SST(vals):
    r = 0
    gm = grand_mean(vals)
    for g in vals:
        for x in g:
            r += (x - gm)**2
    return r

def SSA(vals):
    r = 0
    gm = grand_mean(vals)
    for g in vals:
        r += len(g)*((sum(g)/len(g))-gm)**2
    return r

def SSW(vals):
    r = 0
    for g in vals:
        m = sum(g)/len(g)
        for x in g:
            r += (x - m)**2
    return r

def MSA(vals):
    c = len(vals)
    return SSA(vals)/(c-1)

def MSW(vals):
    c = len(vals)
    n = sum([len(g) for g in vals])
    return SSW(vals)/(n-c)

def MST(vals):
    n = sum([len(g) for g in vals])
    return SST(vals)/(n-1)

def f_stat(vals):
    return MSA(vals)/MSW(vals)

def f_stat2(vals):
    # Should be the same as above
    return stats.f_oneway(*vals)[0]

def p_value(vals):
    return stats.f_oneway(*vals)[1]

def anova(vals):
    # The p-value is the probability of getting an overall test statistic equal to the
    # F-statistic or greater, assuming there is no linear relationship between the
    # dependent variable and the independent variables.

    c = len(vals)
    n = sum([len(g) for g in vals])
    print "Source\t\tDOF\tSofSq\tMean Sq\tF_STAT\t\tp-value"
    print "Among groups:\t%d\t%d\t%d\t%f\t%f" % (c-1, SSA(vals), MSA(vals), f_stat2(vals), p_value(vals))
    print "Within groups:\t%d\t%d\t%d" % (n-c, SSW(vals), MSW(vals))
    print "Total:\t\t%d\t%d" % (n-1, SST(vals))

def tukey_kramer(vals, level_of_significance):
    # Determine which sets differ in their means
    #
    # Q_a is the upper-tail critical value from a Studentized range distribution
    # having c degrees of freedom in the numerator and n-c degrees of freedom
    # in the denominator
    #
    # Returns the pairs of groups which have a significant difference
    means = [sum(x)/len(x) for x in vals]
    pairs = list(itertools.combinations(range(len(vals)), 2))
    abs_mean_diff = [abs(means[a]-means[b]) for a, b in pairs]
    Q_a = q_a(len(vals), sum([len(v) for v in vals])-len(vals), level_of_significance)
    msw = MSW(vals)
    critical_range = [Q_a*math.sqrt((msw/2)*((1/len(vals[a]))+(1/len(vals[b])))) for a,b in pairs]
    return [pairs[i] for i in range(len(pairs)) if abs_mean_diff[i] > critical_range[i]]

# Chapter 13

# r^2 (coefficient of determination) is the interpretation that r^2*100 percent
# of the variation in the dependent variable can be explained by the variation 
# in the independent variable

def regression_coefficients(x, y):
    # Here, X is the independent variable
    b1, b0, _, _, _ = stats.linregress(x, y)
    print "b0=%f, b1=%f" % (b0, b1)
    return (b0, b1)

def regression_equation(b0, b1, Xi):
    return b0 + b1 * Xi

def r2_SS(SSR, SST):
    return SSR/SST

def r2(b0, b1, Yi, Y2i, XiYi, n):
    return r2_SS((b0 * Yi + b1 * XiYi - (Yi**2 / n)), (Y2i - (Yi**2 / n)))

def Syx(b0, b1, Yi, Y2i, XiYi, n):
    return math.sqrt((Y2i - b0 * Yi - b1 * XiYi) / (n - 2))

def residuals(b0, b1, x, y):
    return [yi - regression_equation(b0, b1, xi) for xi, yi in zip(x, y)]

def durbin_watson(e):
    # Where e_i is the residual at time period i
    num = 0
    for i in range(1, len(e)):
        num += (e[i] - e[i-1])**2
    den = sum([e_i**2 for e_i in e])
    return num/den

def t_stat(b1, Sb1, B1=0):
    return (b1-B1)/Sb1

def t_stat_2(alpha, n):
    return stats.t.isf(alpha/2, n-2)

def confidence_interval(b0, b1, Syx, X_bar, SXX, alpha, n, X_i):
    hi = (1/n) + ((X_i-X_bar)**2)/SXX
    t = t_stat_2(alpha, n)
    return (regression_equation(b0, b1, X_i)-t*Syx*math.sqrt(hi), regression_equation(b0, b1, X_i)+t*Syx*math.sqrt(hi))

def prediction_interval(b0, b1, Syx, X_bar, SXX, alpha, n, X_i):
    hi = (1/n) + ((X_i-X_bar)**2)/SXX
    t = t_stat_2(alpha, n)
    return (regression_equation(b0, b1, X_i)-t*Syx*math.sqrt(1+hi), regression_equation(b0, b1, X_i)+t*Syx*math.sqrt(1+hi))


# Chapter 14

# The p-value is the probability of getting an overall test statistic equal to the
# F-statistic or greater, assuming there is no linear relationship between the
# dependent variable and the independent variables.

def multiple_regression(y_array, x_array, round_to=5):
    # Where the x-values is a list of multiple x-coefficients
    y = np.array(y_array)
    x = np.transpose(np.array(x_array))
    model = ols.ols(y, x, 'y', ['x' + str(i+1) for i,x in enumerate(x_array)])
    model.summary()
    for i,b in enumerate(model.b):
        print "b" + str(i) + " = " + str(round(b,round_to))
    return [round(b, round_to) for b in model.b]

def solve_multiple_regression(b_array, x_array):
    # Where the b_array comes from the previous function,
    # and the x_array comes from the problem
    return sum([b*x for b, x in zip(b_array, [1] + x_array)])

def r2_sos(regression_sos, total_sos):
    # Calculate r2 from sum-of-squares values
    return regression_sos/total_sos

def r2_adj(r2, n, k):
    # Where r2 is previously calculated, n is the sample size (total degrees of
    # freedom plus 1), and k is the number of independent variables (regression
    # degrees of freedom)
    return 1 - ((1-r2)*((n-1)/(n-k-1)))

def multiple_residuals(b_array, x_array, y_array):
    # b_array is an array of coefficients from b0 to bi
    # x_array is an array of arrays of x values for x0 to xi
    # >>>> len(x_array) = len(b_array)-1
    # y_array is the array of y values
    ret = []
    for i in range(len(y_array)):
        ret.append(y_array[i] - solve_multiple_regression(b_array, [x[i] for x in x_array]))
    return ret

def estimated_probability(odds_ratio):
    # Just given an odds ratio
    return odds_ratio/(1+odds_ratio)

def estimated_probability_2(b_array, x_array):
    # Given b and x values
    return estimated_probability(math.e**solve_multiple_regression(b_array, x_array))



# Utility

def newd(l):
    for x in l:
        print str(x)
