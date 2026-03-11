#include<iostream>
using namespace std;

int main()
{
    cout<<"Enter the number of elements required: ";
    int n;
    cin>>n;

    int A[n];

    cout<<"Enter the array:"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"Enter element no "<<i+1<<": ";
        cin>>A[i];
    }

    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(A[j] > A[j+1])
            {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }

    cout<<"\nThe sorted array is: ";
    for(int i=0; i<n; i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;

    int N, sum = 0;

    cout<<"Enter the N value: ";
    cin>>N;

    if(N > n || N <= 0)
    {
        cout<<"Invalid N value";
        return 0;
    }

    int start = (n - N) / 2;

    for(int i = start; i < start + N; i++)
    {
        sum += A[i];
    }

    float avg = (float)sum / N;

    cout<<"The average obtained from the middle "<<N<<" elements is: "<<avg;

    return 0;
}