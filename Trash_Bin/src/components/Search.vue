<script lang="ts">
import { defineComponent } from 'vue';
import Query_Creator from './Query_Components/Query_Creator.vue';
    export default defineComponent ({
        components: {
            Query_Creator
        }
    })
</script>

<template>
    <h2>Search Menu</h2>
    <Query_Creator />
</template>