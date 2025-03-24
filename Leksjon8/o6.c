/*
 *
Exercise 6 (optional):

Discrete integral is simply performed by several ways. One approximation[trapezoidal] is given in the image.

http://upload.wikimedia.org/math/4/9/9/499f1d0a17ada2158b49754019f0dc14.png

(See also https://en.wikipedia.org/wiki/Numerical_integration)

Write a function that has the form

float integral(float (*fn)(float x), float a, float b, int n)

which takes in a function that has one floating point argument and return a floating point integrated value.

Once you have the function. Find the integral of f(x) = x, f(x) = x*x


Write a program that uses the integration function for several intervals - a = [0-1000] b = [1000-2000]

You function should output a vector out[1000][1000] where,

out[0][0] is integration value when a = 0, b = 1000
out[1][0] is integration value when a = 1, b = 1000
....
i[999][999] is integration value when a = 999 and b = 1999

See the two dimensions!
Now try to see how long it takes to accomplish this.. Your progamming loop should look like this












for(int i=0;i<1000;i++){
	for(int j=0;j<1000;j++){
		outp[i][j] = integral(fn, a[i], b[j], 100);
	}
}

Try to make this multithreaded -

- One thread per one outer loop[j integrals] and hence only 1000 threads
- One thread per one integral and hence 1000x1000 threads

You can try to see the performance gain and the resource usage in top, htop
 * */
float inner(float a, b){
	
}

float integral(float (*fn), float a, float b, int n){
			
}

