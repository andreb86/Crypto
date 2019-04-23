from __future__ import print_function, division
from pwn import *
import sys


class Core(object):
    """
    Core management of the remote and executable interfaces.
    """
    def __init__(self, p, **kwargs):
        """
        Create the basic interface to interact with remote and local instances
        of a cryptographic oracle.
        :param p: the instance of the oracle.
        """
        self.oracle = None

        # Verify that the oracle is provided by means of a valid string
        if not isinstance(p, str):
            raise TypeError("Please provide a valid path/URI")

        try:
            assert isinstance(kwargs['port'], int)
            self.port = kwargs['port']
            self.uri = p
            self.oracle = remote(p, self.port)
        except (KeyError, PwnlibException):
            try:
                context.update(kwargs)
                self.context = kwargs
                self.path = p
                self.oracle = process(p)
            except (AttributeError, PwnlibException) as e:
                print("Invalid context or process:\n" + e.message)
                sys.exit(-3)
        except AssertionError as ae:
            print(
                "Invalid port, int expected:\n" + ae.message, file=sys.stderr
            )
            sys.exit(-2)
        else:
            print("{0} is an invalid oracle".format(p), file=sys.stderr)
            sys.exit(-1)

    def receive(self, regex=r"\n", wait=5, verbose=True):
        """
        Receive the output stream from a tube up to the regex and print it to
        screen if required.
        :param regex: The regex of the delimiter which feed is received up to
        :param wait: Timeout
        :param verbose: Print the received feed if required
        :return:
        """
        s = self.oracle.recvregex(regex, exact=True, timeout=wait)
        if s == '':
            print("Regex not found or timed out...")
            raise Timeout
        if verbose:
            print(s)

    def __del__(self):
        """
        Destructor
        :return:
        """
        self.oracle.close()
        for base in self.__class__.__bases__:
            # Avoid problems with diamond inheritance.
            base_key = 'del_' + str(base)
            if not hasattr(self, base_key):
                setattr(self, base_key, 1)
            else:
                continue
            # Call this base class' destructor if it has one.
            if hasattr(base, "__del__"):
                base.__del__(self)


