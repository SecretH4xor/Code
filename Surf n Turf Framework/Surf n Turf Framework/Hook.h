
#include <cassert>
namespace VMThook
{
	enum HOOKS
	{
		HK_PAINTTRAVERSE=41,
		HK_CREATEMOVE=21,
		HK_HUDUPDATE=11
	};

	typedef unsigned int uint;

	typedef int int_ptr;

	template< typename T > inline T make_ptr( void* ptr, int_ptr offset ) { return reinterpret_cast<T>( (size_t)ptr + offset ); }

	inline void**& getvtable( void* inst, int_ptr offset = 0 ) { return *reinterpret_cast<void***>( (size_t)inst + offset ); }

	uint CountFuncs( void** pVMT );

	uint CountFuncs( void* begin, void* end, void** pVMT );

	int FindFunc( void** pVMT, void* pFunc, uint vfuncs = 0 );

	class VMTManager
	{
		VMTManager( const VMTManager& );
		VMTManager& operator= ( const VMTManager& );

	public:
		VMTManager( void* inst, size_t offset = 0, uint vfuncs = 0 );
		~VMTManager();

		inline void HookMethod( void* newfunc, size_t index )
		{
			assert( index<_vcount );
			_array[index+3] = newfunc;
		}

		inline void UnhookMethod( size_t index )
		{
			assert( index<_vcount );
			_array[index+3] = _oldvmt[index];
		}

		inline void Unhook() { *_vftable = _oldvmt; }
		inline void Rehook() { *_vftable = _array + 3; }
		inline bool Hooked() const { return *_vftable!=_oldvmt; }
		inline void EraseHooks() { for ( uint i = 0; i<_vcount; ++i ) _array[i+3] = _vftable[i]; }
		inline uint NumFuncs() const { return _vcount; }

		inline void Poof() { _vftable = 0; }

		template< typename Fn >
		inline Fn GetMethod( size_t index ) const
		{
			assert( index<_vcount );
			return (Fn) _oldvmt[ index ];
		}

	protected:
		inline void _set_guard( size_t S ) { _array[1] = (void*) S; }
		inline size_t _get_guard() const { return (size_t) _array[1]; }
		inline void _set_backptr( void* ptr ) { _array[0] = ptr; }
		inline void* _get_backptr() const { return _array[0]; }

	private:
		void***	_vftable;
		void**	_oldvmt;
		void**	_array;
		uint	_vcount;
	};

}